/**
 * @file
 * @brief IsInputIterator
 * @author Bromine0x23
 * @since 2016/6/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_iterator.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief IsInputIterator
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotInputIterator
 *
 */
template< typename T >
struct IsInputIterator;

/**
 * @brief IsInputIterator 的否定
 * @tparam T 待检查类型
 * @see IsInputIterator
 */
template< typename T >
struct NotInputIterator;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsInputIterator 的模板变量版本
 * @tparam T 待检查类型
 * @see IsInputIterator
 * @see not_input_iterator
 */
template< typename T >
constexpr auto is_input_iterator = boolean_constant< IsInputIterator<T> >;

/**
 * @brief NotInputIterator 的模板变量版本
 * @tparam T 待检查类型
 * @see NotInputIterator
 * @see is_input_iterator
 */
template< typename T >
constexpr auto not_input_iterator = boolean_constant< NotInputIterator<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename TIterator >
struct IsInputIteratorBasic : BooleanAnd<
	IsConvertible< typename BR::IteratorTraits<TIterator>::Category, ReadableTag >,
	IsConvertible< typename BR::IteratorTraits<TIterator>::Category, SinglePassTraversalTag >
> {};

template< typename TIterator >
using IsInputIterator = BooleanAnd< IsIterator<TIterator>, IsInputIteratorBasic<TIterator> >;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsInputIterator : public BooleanRewrapPositive< Detail::TypeTraits::IsInputIterator<T> > {};

template< typename T >
struct NotInputIterator : public BooleanRewrapNegative< Detail::TypeTraits::IsInputIterator<T> > {};

} // namespace TypeTraits

} // namespace BR