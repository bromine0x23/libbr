/**
 * @file
 * @brief 迭代器类型信息
 * @author Bromine0x23
 * @since 2015/10/22
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_pointer.hpp>
#include <libbr/type_operate/remove_const.hpp>
#include <libbr/type_operate/template_argument.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_traits/is_convertible.hpp>

namespace BR {

template< typename T >
struct IteratorTraits;

namespace Detail {
namespace TypeTraits {
namespace IteratorTraits {

#define BR_TYPE_OPERATE_TYPE_NAME Category
#include <libbr/type_traits/has_member_type.inc>

#define BR_TYPE_OPERATE_TYPE_NAME Element
#include <libbr/type_traits/has_member_type.inc>

template< typename TIterator, bool _dummy = HasMemberTypeElement<TIterator>::value >
struct TypeElement;

template< typename TIterator >
struct TypeElement< TIterator, true > : TypeWrapper< typename TIterator::Element > {
};

template< typename TIterator >
struct TypeElement< TIterator, false > : FirstTemplateArgument<TIterator> {
};

template< typename TIterator >
using Element = TypeUnwrap< TypeElement<TIterator> >;

#define BR_TYPE_OPERATE_TYPE_NAME Pointer
#include <libbr/type_traits/has_member_type.inc>

template< typename TIterator, bool _dummy = HasMemberTypePointer<TIterator>::value >
struct TypePointer;

template< typename TIterator >
struct TypePointer< TIterator, true > : TypeWrapper< typename TIterator::Pointer > {
};

template< typename TIterator >
struct TypePointer< TIterator, false > : TypeAddPointer< Element<TIterator> > {
};

#define BR_TYPE_OPERATE_TYPE_NAME Reference
#include <libbr/type_traits/has_member_type.inc>

template< typename TIterator, bool _dummy = HasMemberTypeReference<TIterator>::value >
struct TypeReference;

template< typename TIterator >
struct TypeReference< TIterator, true > : TypeWrapper< typename TIterator::Reference > {
};

template< typename TIterator >
struct TypeReference< TIterator, false > : TypeAddLValueReference< Element<TIterator> > {
};

#define BR_TYPE_OPERATE_TYPE_NAME Difference
#include <libbr/type_traits/has_member_type.inc>

template< typename TIterator, bool _dummy = HasMemberTypeDifference<TIterator>::value >
struct TypeDifference;

template< typename TIterator >
struct TypeDifference< TIterator, true > : TypeWrapper< typename TIterator::Difference > {};

template< typename TIterator >
struct TypeDifference< TIterator, false > : TypeWrapper<BR::PointerDifference> {};

template< typename TIterator, bool _dummy = IsConvertible< typename TIterator::Category, IteratorTag >::value >
struct Base;

template< typename TIterator >
struct Base< TIterator, true > {
public:
	using Iterator = TIterator;

	using Category = typename Iterator::Category;

	using Element = IteratorTraits::Element<Iterator>;

	using Pointer = TypeUnwrap< TypePointer<Iterator> >;

	using Reference = TypeUnwrap< TypeReference<Iterator> >;

	using Difference = TypeUnwrap< TypeDifference<Iterator> >;

	static auto category() -> Category {
		return Category();
	}
};

template< typename TIterator >
struct Base< TIterator, false > {
};

template< typename TIterator, bool _dummy = HasMemberTypeCategory<TIterator>::value >
struct Implement;

template< typename TIterator >
struct Implement< TIterator, true > : Base<TIterator> {
};

template< typename TIterator >
struct Implement< TIterator, false > {
};

} // namespace IteratorTraits
} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 迭代器类型信息
 * @tparam T 迭代器类型
 */
template< typename TIterator >
struct IteratorTraits : Detail::TypeTraits::IteratorTraits::Implement<TIterator> {
};

template< typename TElement >
struct IteratorTraits< TElement * > {
public:
	using Iterator = TElement *;

	/**
	 * @brief 迭代器类别
	 */
	using Category = MutableRandomAccessIteratorTag;

	/**
	 * @brief 迭代元素
	 */
	using Element = TElement;

	/**
	 * @brief 元素指针
	 */
	using Pointer = Element *;

	/**
	 * @brief 元素引用
	 */
	using Reference = Element &;

	/**
	 * @brief 求差结果
	 */
	using Difference = PointerDifference;

	static auto category() -> Category {
		return Category();
	}
};

} // namespace BR