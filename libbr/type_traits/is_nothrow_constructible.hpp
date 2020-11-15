/**
 * @file
 * @brief 检查是否可从特定参数 \em nothrow 地构造
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conjunction.hpp>
#if !defined(BR_IS_NOTHROW_CONSTRUCTIBLE)
#  include <libbr/type_traits/is_array.hpp>
#  include <libbr/type_traits/is_constructible.hpp>
#  include <libbr/type_transform/remove_all_extents.hpp>
#  include <libbr/utility/declare_value.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否可从特定参数 \em nothrow 地构造
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see Utility::IntegralConstant
 * @see BR_IS_NOTHROW_CONSTRUCTIBLE
 * @see IsConstructible
 * @see NotNothrowConstructible
 *
 * 如果表达式 <tt>T(BR::make_rvalue<TArgs>()...)</tt> 是合法且不抛出异常的，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T, typename... TArgs >
struct IsNothrowConstructible;

/**
 * @brief IsNothrowConstructible 的否定
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see IsNothrowConstructible
 */
template< typename T, typename... TArgs >
struct NotNothrowConstructible;

/**
 * @brief IsNothrowConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see IsNothrowConstructible
 * @see not_nothrow_constructible
 */
template< typename T, typename... TArgs >
constexpr auto is_nothrow_constructible = boolean_constant< IsNothrowConstructible< T, TArgs... > >;

/**
 * @brief NotNothrowConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see NotNothrowConstructible
 * @see is_nothrow_constructible
 */
template< typename T, typename... TArgs >
constexpr auto not_nothrow_constructible = boolean_constant< NotNothrowConstructible< T, TArgs... > >;

} // namespace TypeTraits



namespace _::TypeTraits {

#if defined(BR_IS_NOTHROW_CONSTRUCTIBLE)

template< typename T, typename... TArgs >
using IsNothrowConstructible = BooleanConstant< BR_IS_NOTHROW_CONSTRUCTIBLE(T, TArgs...) >;

#else

template< typename T >
struct IsNothrowConstructibleZeroBasic : public BooleanConstant< noexcept(T()) > {};

template< typename T >
using IsNothrowConstructibleZero = Conditional<
	IsArray<T>,
	Conjunction<
		IsBoundedArray<T>,
		IsNothrowConstructibleZeroBasic< RemoveAllExtents<T> >
	>,
	IsNothrowConstructibleZeroBasic<T>
>;

template< typename T, typename... TArgs >
struct IsNothrowConstructibleBasic : public BooleanConstant< noexcept(T(declare_value<TArgs>()...)) > {};

template< typename T >
struct IsNothrowConstructibleBasic< T > : public IsNothrowConstructibleZero<T> {};

template< typename T, typename TArg >
struct IsNothrowConstructibleBasic< T, TArg > : public BooleanConstant< noexcept(static_cast<T>(declare_value<TArg>())) > {};

template< typename T, typename... TArgs >
struct IsNothrowConstructible : Conjunction<
	IsConstructible< T, TArgs... >, IsNothrowConstructibleBasic< T, TArgs... >
> {};

#endif // defined(BR_IS_NOTHROW_CONSTRUCTIBLE)

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T, typename... TArgs >
struct IsNothrowConstructible : public BooleanRewrapPositive< _::TypeTraits::IsNothrowConstructible< T, TArgs... > > {};

template< typename T, typename... TArgs >
struct NotNothrowConstructible : public BooleanRewrapNegative< _::TypeTraits::IsNothrowConstructible< T, TArgs... > > {};

} // namespace TypeTraits

} // namespace BR