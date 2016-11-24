/**
 * @file
 * @brief 迭代器类型检查
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_base_of.hpp>
#include <libbr/type_traits/is_pointer.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是迭代器
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IteratorTag
 * @see IsPointer
 * @see NotIterator
 *
 * 如果 \em T 为 \em BasicIterator 的子类，或指针类型，
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsIterator;

/**
 * @brief IsIterator 的否定
 * @tparam T 待检查类型
 * @see IsIterator
 */
template< typename T >
struct NotIterator;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsIterator 的模板变量版本
 * @tparam T 待检查类型
 * @see IsIterator
 * @see not_iterator
 */
template< typename T >
constexpr auto is_iterator = boolean_constant< IsIterator<T> >;

/**
 * @brief NotIterator 的模板变量版本
 * @tparam T 待检查类型
 * @see NotIterator
 * @see is_iterator
 */
template< typename T >
constexpr auto not_iterator = boolean_constant< NotIterator<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
using IsIterator = BooleanOr<
	IsPointer<T>,
	IsBaseOf< BasicIterator, T >
>;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsIterator : BooleanRewrapPositive< Detail::TypeTraits::IsIterator<T> > {};

template< typename T >
struct NotIterator : BooleanRewrapNegative< Detail::TypeTraits::IsIterator<T> > {};

} // namespace TypeTraits

} // namespace BR
