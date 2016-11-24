/**
 * @file
 * @brief 检查是否可被 \em nothrow 地交换
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_swappable.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否可被 \em nothrow 地交换
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see swap
 * @see IsSwappable
 * @see NotNothrowSwappable
 *
 * 如果表达式 <tt>swap(make_reference< T & >(), make_reference< T & >())</tt> 是合法且不抛出异常的，
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsNothrowSwappable;

/**
 * @brief IsNothrowSwappable 的否定
 * @tparam T 待检查类型
 * @see IsNothrowSwappable
 */
template< typename T >
struct NotNothrowSwappable;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsNothrowSwappable 的模板变量版本
 * @tparam T 待检查类型
 * @see IsNothrowSwappable
 * @see not_nothrow_swappable
 */
template< typename T >
constexpr auto is_nothrow_swappable = boolean_constant< IsNothrowSwappable<T> >;

/**
 * @brief NotNothrowSwappable 的模板变量版本
 * @tparam T 待检查类型
 * @see NotNothrowSwappable
 * @see is_nothrow_swappable
 */
template< typename T >
constexpr auto not_nothrow_swappable = boolean_constant< NotNothrowSwappable<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsNothrowSwappableBasic {
	constexpr static auto value = noexcept(swap(make_reference<T>(), make_reference<T>()));
};

template< typename T >
using IsNothrowSwappable = BooleanAnd<
	IsSwappable<T>,
	BooleanConstant< IsNothrowSwappableBasic<T>::value >
>;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsNothrowSwappable : BooleanRewrapPositive< Detail::TypeTraits::IsNothrowSwappable<T> > {};

template< typename T >
struct NotNothrowSwappable : BooleanRewrapNegative< Detail::TypeTraits::IsNothrowSwappable<T> > {};

} // namespace TypeTraits

} // namespace BR

