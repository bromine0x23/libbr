/**
 * @file
 * @brief 检查是否可被交换
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否可被交换
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see BR::swap
 * @see NotSwappable
 *
 * 如果表达式 <tt>swap(make_reference< T & >(), make_reference< T & >())</tt> 是合法的，
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsSwappable;

/**
 * @brief IsSwappable 的否定
 * @tparam T 待检查类型
 * @see IsSwappable
 */
template< typename T >
struct NotSwappable;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsSwappable 的模板变量版本
 * @tparam T 待检查类型
 * @see IsSwappable
 * @see not_swappable
 */
template< typename T >
constexpr auto is_swappable = boolean_constant< IsSwappable<T> >;

/**
 * @brief NotSwappable 的模板变量版本
 * @tparam T 待检查类型
 * @see NotSwappable
 * @see is_swappable
 */
template< typename T >
constexpr auto not_swappable = boolean_constant< NotSwappable<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

using BR::swap;

struct IsSwappableTest {
	template< typename T, typename = decltype(swap(make_reference< T & >(), make_reference< T & >())) >
	static auto test(int) -> BooleanTrue;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

template< typename T >
using IsSwappable = decltype(IsSwappableTest::test<T>(0));

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsSwappable : BooleanRewrapPositive< Detail::TypeTraits::IsSwappable<T> > {};

template< typename T >
struct NotSwappable : BooleanRewrapNegative< Detail::TypeTraits::IsSwappable<T> > {};

} // namespace TypeTraits

} // namespace BR