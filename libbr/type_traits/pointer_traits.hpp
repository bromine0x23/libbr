#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/replace_template_argument.hpp>
#include <libbr/type_operate/template_argument.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_traits/is_void.hpp>

namespace BR {

template< typename TPointer >
struct PointerTraits;

namespace Detail {
namespace TypeTraits {
namespace PointerTraitsHelper {

#define BR_TYPE_OPERATE_TYPE_NAME Element
#include <libbr/type_traits/has_member_type.inc>

template< typename TPointer, bool = HasMemberTypeElement<TPointer>::value >
struct TypeElement;

template< typename TPointer >
struct TypeElement< TPointer, true > : TypeWrapper< typename TPointer::Element > {};

template< typename TPointer >
struct TypeElement< TPointer, false > : TypeFirstTemplateArgument<TPointer> {};

#define BR_TYPE_OPERATE_TYPE_NAME Difference
#include <libbr/type_traits/has_member_type.inc>

template< typename TPointer, bool = HasMemberTypeDifference<TPointer>::value >
struct TypeDifference;

template< typename TPointer >
struct TypeDifference< TPointer, true > : TypeWrapper< typename TPointer::Difference > {};

template< typename TPointer >
struct TypeDifference< TPointer, false > : TypeWrapper<BR::PointerDifference> {};

#define BR_TYPE_OPERATE_TYPE_NAME Rebind
#include <libbr/type_traits/has_member_type.inc>

template< typename TPointer, typename TElement, bool = HasMemberTypeRebind<TPointer>::value >
struct TypeRebind;

template< typename TPointer, typename TElement >
struct TypeRebind< TPointer, TElement, true > : TypeWrapper< typename TPointer::template Rebind<TElement> > {};

template< typename TPointer, typename TElement >
struct TypeRebind< TPointer, TElement, false > : TypeReplaceFirstTemplateArgument< TPointer, TElement > {};

} // namespace PointerTraitsHelper
} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 指针特性类
 * @tparam TPointer 指针类型
 */
template< typename TPointer >
struct PointerTraits {
private:
	struct NAT {
	};

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
	using Element = TypeUnwrap< Detail::TypeTraits::PointerTraitsHelper::TypeElement<Pointer> >;

	/**
	 * @brief 两指针求差的结果类型
	 * @see BR::PointerDifference
	 *
	 * 如果 <tt>Pointer::Difference</tt> 存在则为该类型；
	 * 否则，为 PointerDifference
	 */
	using Difference = TypeUnwrap< Detail::TypeTraits::PointerTraitsHelper::TypeDifference<Pointer> >;

	/**
	 * @brief 绑定到新的元素类型
	 * @tparam TNewElement 新的元素类型
	 *
	 * 如果 <tt>Pointer::Rebind<TNewElement></tt> 存在则为该类型；
	 * 否则，如果 \em Pointer 是一个模板实例 <tt>Template< T, TArgs... ></tt>，则为类型 <tt>Template< TNewElement, TArgs... ></tt>
	 */
	template< typename TOtherElement >
	using Rebind = TypeUnwrap< Detail::TypeTraits::PointerTraitsHelper::TypeRebind< Pointer, TOtherElement > >;

	/**
	 * @brief 包装引用为指针
	 * @pre \em Element 不是 \em void
	 */
	static Pointer make_pointer(Conditional< IsVoid<Element>, NAT, Element > & reference) {
		return Pointer::make_pointer(reference);
	}
/*
	static auto to_raw(Pointer pointer) -> decltype(pointer.operator->()) {
		return pointer.operator->();
	}
 */
};

/**
* @brief 指针特性类对原生指针的特化
*/
template< typename TElement >
struct PointerTraits< TElement * > {
private:
	struct NAT {
	};

public:
	using Element = TElement;
	using Pointer = Element *;
	using Difference = PointerDifference;

	template< typename TOtherElement >
	using Rebind = TOtherElement *;

	static Pointer make_pointer(Conditional< IsVoid<Element>, NAT, Element > & reference) {
		return address_of(reference);
	}
/*
	static auto to_raw(Pointer pointer) -> Pointer {
		return pointer;
	}
 */
};

} // namespace BR
