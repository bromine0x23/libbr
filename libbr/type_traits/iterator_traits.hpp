/**
 * @file
 * @brief 迭代器特性类
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/add_lvalue_reference.hpp>
#include <libbr/type_traits/add_pointer.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/has_member_type.hpp>
#include <libbr/type_traits/remove_const.hpp>
#include <libbr/type_traits/template_argument.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * 迭代器特性类
 * @tparam TIterator 分配器类型
 */
template< typename TIterator >
struct IteratorTraits;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {
namespace IteratorTraits {

////////////////////////////////
//
// IteratorTraits::Category
//
BR_HAS_MEMBER_TYPE(Category);

template< typename TIterator, bool = HasMemberTypeCategory<TIterator>{} >
struct TypeCategory;

template< typename TIterator >
struct TypeCategory< TIterator, true > : TypeWrapper< typename TIterator::Category > {};

template< typename TIterator >
struct TypeCategory< TIterator, false > : TypeWrapper< IteratorTag > {};

template< typename TIterator >
using Category = typename TIterator::Category;

////////////////////////////////
//
// IteratorTraits::Element
//
BR_HAS_MEMBER_TYPE(Element);

template< typename TIterator, bool = HasMemberTypeElement<TIterator>{} >
struct TypeElement;

template< typename TIterator >
struct TypeElement< TIterator, true > : TypeWrapper< typename TIterator::Element > {};

template< typename TIterator >
struct TypeElement< TIterator, false > : TypeFirstTemplateArgument<TIterator> {};

template< typename TIterator >
using Element = TypeUnwrap< TypeElement<TIterator> >;

////////////////////////////////
//
// IteratorTraits::Pointer
//
BR_HAS_MEMBER_TYPE(Pointer);

template< typename TIterator, bool = HasMemberTypePointer<TIterator>{} >
struct TypePointer;

template< typename TIterator >
struct TypePointer< TIterator, true > : TypeWrapper< typename TIterator::Pointer > {};

template< typename TIterator >
struct TypePointer< TIterator, false > : TypeAddPointer< Element<TIterator> > {};

////////////////////////////////
//
// IteratorTraits::Reference
//
BR_HAS_MEMBER_TYPE(Reference);

template< typename TIterator, bool = HasMemberTypeReference<TIterator>{} >
struct TypeReference;

template< typename TIterator >
struct TypeReference< TIterator, true > : TypeWrapper< typename TIterator::Reference > {};

template< typename TIterator >
struct TypeReference< TIterator, false > : TypeAddLValueReference< Element<TIterator> > {};

////////////////////////////////
//
// IteratorTraits::Difference
//
BR_HAS_MEMBER_TYPE(Difference);

template< typename TIterator, bool = HasMemberTypeDifference<TIterator>{} >
struct TypeDifference;

template< typename TIterator >
struct TypeDifference< TIterator, true > : TypeWrapper< typename TIterator::Difference > {};

template< typename TIterator >
struct TypeDifference< TIterator, false > : TypeWrapper<BR::PointerDifference> {};



template< typename TIterator, bool = IsConvertible< typename TIterator::Category, IteratorTag >{} >
struct Base;

template< typename TIterator >
struct Base< TIterator, true > {
public:
	using Iterator = TIterator;

	using Category = typename Iterator::Category;

	static_assert(IsEmpty<Category>{}, "`Category` should be an empty type.");

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

template< typename TIterator, bool = HasMemberTypeCategory<TIterator>{} >
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

inline namespace TypeTraits {

template< typename TIterator >
struct IteratorTraits : Detail::TypeTraits::IteratorTraits::Implement<TIterator> {};

template< typename TElement >
struct IteratorTraits< TElement * > {
public:
	/**
	 * @brief 迭代器类型
	 */
	using Iterator = TElement *;

	/**
	 * @brief 迭代器类别
	 */
	struct Category : public IteratorTag, public ReadableTag, public WritableTag, public RandomAccessTraversalTag {
	};

	static_assert(IsEmpty<Category>{}, "`Category` should be an empty type.");

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

} // namespace TypeTraits

} // namespace BR