/**
 * @file
 * @brief IsForwardIterator
 * @since 1.0
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
 * @brief IsForwardIterator
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotInputIterator
 *
 */
template< typename T >
struct IsForwardIterator;

/**
 * @brief IsForwardIterator 的否定
 * @tparam T 待检查类型
 * @see IsForwardIterator
 */
template< typename T >
struct NotForwardIterator;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsForwardIterator 的模板变量版本
 * @tparam T 待检查类型
 * @see IsForwardIterator
 * @see not_forward_iterator
 */
template< typename T >
constexpr auto is_forward_iterator = boolean_constant< IsForwardIterator<T> >;

/**
 * @brief NotForwardIterator 的模板变量版本
 * @tparam T 待检查类型
 * @see NotForwardIterator
 * @see is_forward_iterator
 */
template< typename T >
constexpr auto not_forward_iterator = boolean_constant< NotForwardIterator<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename TIterator >
struct IsForwardIteratorBasic : BooleanAnd<
	IsConvertible< typename BR::IteratorTraits<TIterator>::Category, ReadableTag >,
	IsConvertible< typename BR::IteratorTraits<TIterator>::Category, ForwardTraversalTag >
> {};

template< typename TIterator >
struct IsForwardIterator : public BooleanAnd< IsIterator<TIterator>, IsForwardIteratorBasic<TIterator> > {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsForwardIterator : public BooleanRewrapPositive< Detail::TypeTraits::IsForwardIterator<T> > {};

template< typename T >
struct NotForwardIterator : public BooleanRewrapNegative< Detail::TypeTraits::IsForwardIterator<T> > {};

} // namespace TypeTraits

} // namespace BR