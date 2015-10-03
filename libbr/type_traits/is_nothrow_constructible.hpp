/**
 * @file
 * @brief 检查是否重载了 \em nothrow 的构造函数
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_traits/is_nothrow_default_constructible.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T, typename... TArgs >
struct IsNothrowConstructibleBasic;

template< typename T >
struct IsNothrowConstructibleBasic< T > : IsNothrowDefaultConstructible<T> {};

template< typename T, typename TArg >
struct IsNothrowConstructibleBasic< T, TArg > : BooleanConstant< noexcept(static_cast<T>(make_rvalue<TArg>())) > {};

template< typename T, typename... TArgs >
struct IsNothrowConstructibleBasic : BooleanConstant< noexcept(T(make_rvalue<TArgs>() ...)) > {};

template< typename T, typename... TArgs >
using IsNothrowConstructible = BooleanAnd<
	IsConstructible< T, TArgs... >,
	IsNothrowConstructibleBasic< T, TArgs... >
>;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否重载了特定参数的 \em nothrow 构造函数
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数类型
 * @see IntegerConstant
 * @see IsConstructible
 * @see NotNothrowConstructible
 *
 * 如果表达式 <tt>T(BR::make_rvalue<TArgs>()...)</tt> 是合法且不抛出异常的，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T, typename... TArgs >
struct IsNothrowConstructible : BooleanRewrapPositive< Detail::TypeTraits::IsNothrowConstructible< T, TArgs... > > {};

/**
 * @brief IsNothrowConstructible 的否定
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see IsNothrowConstructible
 */
template< typename T, typename... TArgs >
struct NotNothrowConstructible : BooleanRewrapNegative< Detail::TypeTraits::IsNothrowConstructible< T, TArgs... > > {};

#if defined(BR_CXX14)

/**
 * @brief IsNothrowConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see IsNothrowConstructible
 * @see not_nothrow_constructible
 */
template< typename T, typename TArg >
constexpr auto is_nothrow_constructible = bool_constant< IsNothrowConstructible< T, TArg > >;

/**
 * @brief NotNothrowConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see NotNothrowConstructible
 * @see is_nothrow_constructible
 */
template< typename T, typename TArg >
constexpr auto not_nothrow_constructible = bool_constant< NotNothrowConstructible< T, TArg > >;

#endif // defined(BR_CXX14)

} // namespace BR