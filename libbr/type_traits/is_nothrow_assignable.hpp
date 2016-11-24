/**
 * @file
 * @brief 检查是否重载了 \em nothrow 的赋值运算符
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_NOTHROW_ASSIGNABLE)
#  include <libbr/type_traits/is_assignable.hpp>
#  include <libbr/utility/make_value.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否重载了特定参数的 \em nothrow 赋值运算符
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see IntegerConstant
 * @see IsAssignable
 * @see NotNothrowAssignable
 *
 * 如果表达式 <tt>BR::make_rvalue<T>() = BR::make_rvalue<TSrc>()</tt> 在非求值上下文中是合法且不抛出异常的，
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename T, typename TArg >
struct IsNothrowAssignable;

/**
 * @brief IsNothrowAssignable 的否定
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see IsNothrowAssignable
 */
template< typename T, typename TArg >
struct NotNothrowAssignable;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsNothrowAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see IsNothrowAssignable
 * @see not_nothrow_assignable
 */
template< typename T, typename TArg >
constexpr auto is_nothrow_assignable = boolean_constant< IsNothrowAssignable< T, TArg > >;

/**
 * @brief NotNothrowAssignable 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArg 赋值参数
 * @see NotNothrowAssignable
 * @see is_nothrow_assignable
 */
template< typename T, typename TArg >
constexpr auto not_nothrow_assignable = boolean_constant< NotNothrowAssignable< T, TArg > >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_NOTHROW_ASSIGNABLE)

template< typename T, typename TArg >
using IsNothrowAssignable = BooleanConstant< BR_IS_CONSTRUCTIBLE(T, TArg) >;

#else

template< typename T, typename TArg >
struct IsNothrowAssignableBasic : public BooleanConstant< noexcept(make_rvalue<T>() = make_rvalue<TArg>()) > {};

template< typename T, typename TArg >
struct IsNothrowAssignable : public BooleanAnd< IsAssignable< T, TArg >, IsNothrowAssignableBasic< T, TArg > > {};

#endif

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T, typename TArg >
struct IsNothrowAssignable : public BooleanRewrapPositive< Detail::TypeTraits::IsNothrowAssignable< T, TArg > > {};

template< typename T, typename TArg >
struct NotNothrowAssignable : public BooleanRewrapNegative< Detail::TypeTraits::IsNothrowAssignable< T, TArg > > {};

} // namespace TypeTraits

} // namespace BR