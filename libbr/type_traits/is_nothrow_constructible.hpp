/**
 * @file
 * @brief 检查是否可从特定参数 \em nothrow 地构造
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_NOTHROW_CONSTRUCTIBLE)
#  include <libbr/type_traits/is_constructible.hpp>
#  include <libbr/utility/make_value.hpp>
#endif

namespace BR {

/**
 * @brief 检查 \em T 是否可从特定参数 \em nothrow 地构造
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see BR::IntegerConstant
 * @see BR_IS_NOTHROW_CONSTRUCTIBLE
 * @see BR::IsConstructible
 * @see BR::NotNothrowConstructible
 *
 * 如果表达式 <tt>T(BR::make_rvalue<TArgs>()...)</tt> 是合法且不抛出异常的，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T, typename... TArgs >
struct IsNothrowConstructible;

/**
 * @brief IsNothrowConstructible 的否定
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see BR::IsNothrowConstructible
 */
template< typename T, typename... TArgs >
struct NotNothrowConstructible;

#if defined(BR_CXX14)

/**
 * @brief IsNothrowConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see BR::IsNothrowConstructible
 * @see BR::not_nothrow_constructible
 */
template< typename T, typename... TArgs >
constexpr auto is_nothrow_constructible = bool_constant< IsNothrowConstructible< T, TArgs... > >;

/**
 * @brief NotNothrowConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see BR::NotNothrowConstructible
 * @see BR::is_nothrow_constructible
 */
template< typename T, typename... TArgs >
constexpr auto not_nothrow_constructible = bool_constant< NotNothrowConstructible< T, TArgs... > >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_NOTHROW_CONSTRUCTIBLE)

template< typename T, typename... TArgs >
using IsNothrowConstructible = BooleanConstant< BR_IS_NOTHROW_CONSTRUCTIBLE(T, TArgs...) >;

#else

template< typename T, typename... TArgs >
struct IsNothrowConstructibleBasic;

template< typename T >
struct IsNothrowConstructibleBasic< T > : public BooleanConstant< noexcept(T()) > {};

template< typename T, typename TArg >
struct IsNothrowConstructibleBasic< T, TArg > : public BooleanConstant< noexcept(static_cast<T>(make_rvalue<TArg>())) > {};

template< typename T, typename... TArgs >
struct IsNothrowConstructibleBasic : public BooleanConstant< noexcept(T(make_rvalue<TArgs>() ...)) > {};

template< typename T, typename... TArgs >
using IsNothrowConstructible = BooleanAnd< IsConstructible< T, TArgs... >, IsNothrowConstructibleBasic< T, TArgs... > >;

#endif // defined(BR_IS_NOTHROW_CONSTRUCTIBLE)

} // namespace TypeTraits
} // namespace Detail

template< typename T, typename... TArgs >
struct IsNothrowConstructible : public BooleanRewrapPositive< Detail::TypeTraits::IsNothrowConstructible< T, TArgs... > > {};

template< typename T, typename... TArgs >
struct NotNothrowConstructible : public BooleanRewrapNegative< Detail::TypeTraits::IsNothrowConstructible< T, TArgs... > > {};

} // namespace BR