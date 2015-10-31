/**
 * @file
 * @brief 检查是否可从特定参数 \em trivially 地构造
 * @author Bromine0x23
 * @since 2015/10/4
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_TRIVIALLY_CONSTRUCTIBLE)
#  include <libbr/type_operate/remove_const.hpp>
#  include <libbr/type_operate/remove_reference.hpp>
#  include <libbr/type_traits/is_same.hpp>
#  include <libbr/type_traits/is_scalar.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_TRIVIALLY_CONSTRUCTIBLE)

template< typename T, typename... TArgs >
using IsTriviallyConstructible = BooleanConstant< BR_IS_TRIVIALLY_CONSTRUCTIBLE(T, TArgs...) >;

#else

template< typename T, typename TArg >
using IsTriviallyConstructibleOne = BooleanAnd< IsSame< T, TArg >, IsScalar<T> >;

template< typename T, typename... TArgs >
struct IsTriviallyConstructible : BooleanFalse {};

template< typename T >
struct IsTriviallyConstructible<T> : IsScalar<T> {};

template< typename T, typename TArg >
struct IsTriviallyConstructible< T, TArg > : IsTriviallyConstructibleOne< T, RemoveConst< RemoveReference<TArg> > > {};

#endif // defined(BR_IS_TRIVIALLY_CONSTRUCTIBLE)

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否可从特定参数 \em trivially 地构造
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see BR::IntegerConstant
 * @see BR_IS_TRIVIALLY_CONSTRUCTIBLE
 * @see BR::IsConstructible
 * @see BR::NotTriviallyConstructible
 *
 * 如果表达式 <tt>T(BR::make_rvalue<TArgs>()...)</tt> 是合法且不抛出异常的，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T, typename... TArgs >
struct IsTriviallyConstructible : BooleanRewrapPositive< Detail::TypeTraits::IsTriviallyConstructible< T, TArgs... > > {};

/**
 * @brief IsTriviallyConstructible 的否定
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see BR::IsTriviallyConstructible
 */
template< typename T, typename... TArgs >
struct NotTriviallyConstructible : BooleanRewrapNegative< Detail::TypeTraits::IsTriviallyConstructible< T, TArgs... > > {};

#if defined(BR_CXX14)

/**
 * @brief IsTriviallyConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see BR::IsTriviallyConstructible
 * @see BR::not_trivially_constructible
 */
template< typename T, typename... TArgs >
constexpr auto is_trivially_constructible = bool_constant< IsTriviallyConstructible< T, TArgs... > >;

/**
 * @brief NotTriviallyConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see BR::NotTriviallyConstructible
 * @see BR::is_trivially_constructible
 */
template< typename T, typename... TArgs >
constexpr auto not_trivially_constructible = bool_constant< NotTriviallyConstructible< T, TArgs... > >;

#endif // defined(BR_CXX14)

} // namespace BR