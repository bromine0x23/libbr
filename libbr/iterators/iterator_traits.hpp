/**
 * @file
 * @brief 迭代器特性类
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_empty.hpp>
#include <libbr/type_traits/has_member_type.hpp>
#include <libbr/type_transform/add_lvalue_reference.hpp>
#include <libbr/type_transform/add_pointer.hpp>
#include <libbr/type_transform/remove_const.hpp>
#include <libbr/type_transform/first_template_argument.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace Iterators {

/**
 * 迭代器特性类
 * @tparam TIterator 分配器类型
 */
template< typename TIterator >
struct IteratorTraits;

} // namespace Iterators



namespace _ {
namespace Iterators {
namespace _ {
namespace IteratorTraits {

////////////////////////////////
//
// IteratorTraits::Category
//
BR_HAS_MEMBER_TYPE(IteratorCategory)

template<typename TIterator, Boolean = has_member_type_IteratorCategory<TIterator>>
struct TypeIteratorCategory;

template<typename TIterator>
struct TypeIteratorCategory<TIterator, true> : TypeWrapper<typename TIterator::Category> {};

template<typename TIterator>
struct TypeIteratorCategory<TIterator, false> : TypeWrapper<CategoryWithTags<>> {};

template<typename TIterator>
using IteratorCategory = TypeUnwrap<TypeIteratorCategory<TIterator>>;

////////////////////////////////
//
// IteratorTraits::Element
//
BR_HAS_MEMBER_TYPE(Element)

template<typename TIterator, Boolean = has_member_type_Element<TIterator>>
struct TypeElement;

template<typename TIterator>
struct TypeElement<TIterator, true> : TypeWrapper<typename TIterator::Element> {};

template<typename TIterator>
struct TypeElement<TIterator, false> : TypeFirstTemplateArgument<TIterator> {};

template<typename TIterator>
using Element = TypeUnwrap<TypeElement<TIterator>>;

////////////////////////////////
//
// IteratorTraits::Pointer
//
BR_HAS_MEMBER_TYPE(Pointer)

template<typename TIterator, Boolean = has_member_type_Pointer<TIterator>>
struct TypePointer;

template<typename TIterator>
struct TypePointer<TIterator, true> : TypeWrapper<typename TIterator::Pointer> {};

template<typename TIterator>
struct TypePointer<TIterator, false> : TypeAddPointer<Element<TIterator>> {};

template<typename TIterator>
using Pointer = TypeUnwrap<TypePointer<TIterator>>;

////////////////////////////////
//
// IteratorTraits::Reference
//
BR_HAS_MEMBER_TYPE(Reference)

template<typename TIterator, Boolean = has_member_type_Reference<TIterator>>
struct TypeReference;

template<typename TIterator>
struct TypeReference<TIterator, true> : TypeWrapper<typename TIterator::Reference> {};

template<typename TIterator>
struct TypeReference<TIterator, false> : TypeAddLValueReference<Element<TIterator>> {};

template<typename TIterator>
using Reference = TypeUnwrap<TypeReference<TIterator>>;

////////////////////////////////
//
// IteratorTraits::Difference
//
BR_HAS_MEMBER_TYPE(Difference)

template<typename TIterator, Boolean = has_member_type_Difference<TIterator>>
struct TypeDifference;

template<typename TIterator>
struct TypeDifference<TIterator, true> : TypeWrapper<typename TIterator::Difference> {};

template<typename TIterator>
struct TypeDifference<TIterator, false> : TypeWrapper<PointerDifference> {};

template<typename TIterator>
using Difference = TypeUnwrap<TypeDifference<TIterator>>;

template<typename TIterator>
struct Base {
public:
	using Iterator = TIterator;

	using IteratorCategory = IteratorTraits::IteratorCategory<Iterator>;

	static_assert(is_empty<IteratorCategory>, "`IteratorCategory` should be an empty type.");

	using Element = IteratorTraits::Element<Iterator>;

	using Pointer = IteratorTraits::Pointer<Iterator>;

	using Reference = IteratorTraits::Reference<Iterator>;

	using Difference = IteratorTraits::Difference<Iterator>;

	constexpr static auto iterator_category() -> IteratorCategory {
		return IteratorCategory();
	}
};

template<typename TIterator, bool = has_member_type_IteratorCategory<TIterator>>
struct Implement;

template<typename TIterator>
struct Implement<TIterator, true> : Base<TIterator> {};

template<typename TIterator>
struct Implement<TIterator, false> {};

} // namespace IteratorTraits
} // namespace _
} // namespace Iterators
} // namespace _

inline namespace Iterators {

template< typename TIterator >
struct IteratorTraits : _::Iterators::_::IteratorTraits::Implement<TIterator> {};

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
	struct IteratorCategory : public ReadableTag, public WritableTag, public RandomAccessTraversalTag, public ContiguousStorageTag {
	};

	static_assert(is_empty<IteratorCategory>, "`IteratorCategory` should be an empty type.");

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

	constexpr static auto iterator_category() -> IteratorCategory {
		return IteratorCategory();
	}
};

} // namespace Iterators

} // namespace BR