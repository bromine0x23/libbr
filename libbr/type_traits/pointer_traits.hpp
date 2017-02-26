/**
 * @file
 * @brief 指针特性类
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_member_type.hpp>
#include <libbr/type_traits/is_void.hpp>
#include <libbr/type_traits/replace_template_argument.hpp>
#include <libbr/type_traits/template_argument.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief Provides information about pointer-like types.
 * @tparam TPointer pointer-like type
 */
template< typename TPointer >
struct PointerTraits;

} // inline namespace TypeTraits



namespace Detail {
namespace TypeTraits {
namespace PointerTraits {

////////////////////////////////
//
// PointerTraits::Element
//
BR_HAS_MEMBER_TYPE(Element)

template< typename TPointer, bool = HasMemberTypeElement<TPointer>{} >
struct TypeElement;

template< typename TPointer >
struct TypeElement< TPointer, true > : TypeWrapper< typename TPointer::Element > {};

template< typename TPointer >
struct TypeElement< TPointer, false > : TypeFirstTemplateArgument<TPointer> {};

template< typename TPointer >
using Element = TypeUnwrap< TypeElement<TPointer> >;

////////////////////////////////
//
// PointerTraits::Difference
//
BR_HAS_MEMBER_TYPE(Difference)

template< typename TPointer, bool = HasMemberTypeDifference<TPointer>{} >
struct TypeDifference;

template< typename TPointer >
struct TypeDifference< TPointer, true > : TypeWrapper< typename TPointer::Difference > {};

template< typename TPointer >
struct TypeDifference< TPointer, false > : TypeWrapper<BR::PointerDifference> {};

template< typename TPointer >
using Difference = TypeUnwrap< TypeDifference<TPointer> >;

////////////////////////////////
//
// PointerTraits::Rebind
//
BR_HAS_MEMBER_TYPE(Rebind)

template< typename TPointer, typename TElement, bool = HasMemberTypeRebind<TPointer>{} >
struct TypeRebind;

template< typename TPointer, typename TElement >
struct TypeRebind< TPointer, TElement, true > : TypeWrapper< typename TPointer::template Rebind<TElement> > {};

template< typename TPointer, typename TElement >
struct TypeRebind< TPointer, TElement, false > : TypeReplaceFirstTemplateArgument< TPointer, TElement > {};

template< typename TPointer, typename TElement >
using Rebind = TypeUnwrap< TypeRebind< TPointer, TElement > >;

} // namespace PointerTraits
} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename TPointer >
struct PointerTraits {
public:
	/**
	 * @brief TPointer
	 */
	using Pointer = TPointer;

	/**
	 * @brief Type of referenced value.
	 *
	 * <code>Pointer::Element</code> if present.
	 * Otherwise <code>T</code> if <code>Pointer</code>  is a template instantiation <code>Template\<T, Args...\></tt>.
	 */
	using Element = Detail::TypeTraits::PointerTraits::Element<Pointer>;

	/**
	 * @brief Type of difference between two <code>Pointer</code>s.
	 *
	 * <code>Pointer::Difference</code> if present.
	 * Otherwise <code>BR::PointerDifference</code>.
	 *
	 * @see BR::PointerDifference
	 */
	using Difference = Detail::TypeTraits::PointerTraits::Difference<Pointer>;

	/**
	 * @brief Bind referenced type to <code>TNewElement</code>.
	 * @tparam TNewElement new element
	 *
	 * <code>Pointer::Rebind\<TNewElement\></code> if exists.
	 * Otherwise <code>Template\<TNewElement, Args...\></tt> if <code>Pointer</code> is a template instantiation <code>Template\<T, Args...\></tt>.
	 */
	template< typename TOtherElement >
	using Rebind = Detail::TypeTraits::PointerTraits::Rebind< Pointer, TOtherElement >;

private:
	struct NAT {};

public:
	/**
	 * @brief Obtains a dereferenceable pointer to its argument.
	 * @pre Element is not <code>void</code>.
	 * @param reference Reference to an object of type <code>Element &</code>.
	 * @return A dereferenceable pointer to \p reference, of the type <code>Pointer</code>.
	 */
	static auto make_pointer(Conditional< IsVoid<Element>, NAT, Element > & reference) -> Pointer {
		return Pointer::make_pointer(reference);
	}

	static auto to_raw(Pointer pointer) -> Element * {
		using Traits = PointerTraits< decltype(pointer.operator->()) >;
		return Traits::to_raw(pointer.operator->());
	}
};

/**
 * @brief A specialization of PointerTraits provided for <code>TElement *</code>.
 */
template< typename TElement >
struct PointerTraits< TElement * > {

public:
	using Element = TElement;
	using Pointer = Element *;
	using Difference = PointerDifference;

	template< typename TOtherElement >
	using Rebind = TOtherElement *;

private:
	struct NAT {};

public:
	static auto make_pointer(Conditional< IsVoid<Element>, NAT, Element > & reference) -> Pointer {
		return address_of(reference);
	}

	static auto to_raw(Pointer pointer) -> Element * {
		return pointer;
	}
};

template< typename TPointer >
inline auto pointer_to_raw(TPointer pointer) -> typename PointerTraits<TPointer>::Element * {
	return PointerTraits<TPointer>::to_raw(pointer);
}

} // inline namespace TypeTraits

} // namespace BR
