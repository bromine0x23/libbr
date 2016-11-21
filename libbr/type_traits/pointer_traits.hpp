/**
 * @file
 * @brief 指针特性类
 * @author Bromine0x23
 * @since 2016/10/9
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/replace_template_argument.hpp>
#include <libbr/type_operate/template_argument.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_traits/has_member_type.hpp>
#include <libbr/type_traits/is_void.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * 指针特性类
 * @tparam TPointer 指针类型
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
	 * @brief 指针类型，即 \em TPointer
	 */
	using Pointer = TPointer;

	/**
	 * @brief 指针指向的元素类型
	 *
	 * 如果 <tt>Pointer::Element</tt> 存在则为该类型；
	 * 否则，如果 \em Pointer 是一个模板实例 <tt>Template< T, TArgs... ></tt>，则为类型 \em T
	 */
	using Element = Detail::TypeTraits::PointerTraits::Element<Pointer>;

	/**
	 * @brief 两指针求差的结果类型
	 * @see BR::PointerDifference
	 *
	 * 如果 <tt>Pointer::Difference</tt> 存在则为该类型；
	 * 否则，为 PointerDifference
	 */
	using Difference = Detail::TypeTraits::PointerTraits::Difference<Pointer>;

	/**
	 * @brief 绑定到新的元素类型
	 * @tparam TNewElement 新的元素类型
	 *
	 * 如果 <tt>Pointer::Rebind<TNewElement></tt> 存在则为该类型；
	 * 否则，如果 \em Pointer 是一个模板实例 <tt>Template< T, TArgs... ></tt>，则为类型 <tt>Template< TNewElement, TArgs... ></tt>
	 */
	template< typename TOtherElement >
	using Rebind = Detail::TypeTraits::PointerTraits::Rebind< Pointer, TOtherElement >;

private:
	struct NAT {};

public:
	/**
	 * @brief 包装引用为指针
	 * @pre \em Element 不是 \em void
	 */
	static Pointer make_pointer(Conditional< IsVoid<Element>, NAT, Element > & reference) {
		return Pointer::make_pointer(reference);
	}

	static auto to_raw(Pointer pointer) -> Element * {
		using Traits = PointerTraits< decltype(pointer.operator->()) >;
		return Traits::to_raw(pointer.operator->());
	}
};

/**
 * @brief 指针特性类对原生指针的特化
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
	static Pointer make_pointer(Conditional< IsVoid<Element>, NAT, Element > & reference) {
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
