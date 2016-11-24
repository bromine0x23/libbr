/**
 * @file
 * @brief 检查是否可从特定参数 \em trivially 地构造
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_TRIVIALLY_CONSTRUCTIBLE)
#  include <libbr/type_traits/is_same.hpp>
#  include <libbr/type_traits/is_scalar.hpp>
#  include <libbr/type_traits/remove_const.hpp>
#  include <libbr/type_traits/remove_reference.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否可从特定参数 \em trivially 地构造
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see IntegerConstant
 * @see BR_IS_TRIVIALLY_CONSTRUCTIBLE
 * @see IsConstructible
 * @see NotTriviallyConstructible
 *
 * 如果表达式 <tt>T(BR::make_rvalue<TArgs>()...)</tt> 是合法且不抛出异常的，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T, typename... TArgs >
struct IsTriviallyConstructible;

/**
 * @brief IsTriviallyConstructible 的否定
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see IsTriviallyConstructible
 */
template< typename T, typename... TArgs >
struct NotTriviallyConstructible;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsTriviallyConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see IsTriviallyConstructible
 * @see not_trivially_constructible
 */
template< typename T, typename... TArgs >
constexpr auto is_trivially_constructible = boolean_constant< IsTriviallyConstructible< T, TArgs... > >;

/**
 * @brief NotTriviallyConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @tparam TArgs 构造函数参数
 * @see NotTriviallyConstructible
 * @see is_trivially_constructible
 */
template< typename T, typename... TArgs >
constexpr auto not_trivially_constructible = boolean_constant< NotTriviallyConstructible< T, TArgs... > >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_TRIVIALLY_CONSTRUCTIBLE)

template< typename T, typename... TArgs >
using IsTriviallyConstructible = BooleanConstant< BR_IS_TRIVIALLY_CONSTRUCTIBLE(T, TArgs...) >;

#else

template< typename T, typename TArg >
using IsTriviallyConstructibleOne = BooleanAnd< IsSame< T, TArg >, IsScalar<T> >;

template< typename T, typename... TArgs >
struct IsTriviallyConstructible : public BooleanFalse {};

template< typename T >
struct IsTriviallyConstructible<T> : public IsScalar<T> {};

template< typename T, typename TArg >
struct IsTriviallyConstructible< T, TArg > : public IsTriviallyConstructibleOne< T, RemoveConst< RemoveReference<TArg> > > {};

#endif // defined(BR_IS_TRIVIALLY_CONSTRUCTIBLE)

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T, typename... TArgs >
struct IsTriviallyConstructible : public BooleanRewrapPositive< Detail::TypeTraits::IsTriviallyConstructible< T, TArgs... > > {};

template< typename T, typename... TArgs >
struct NotTriviallyConstructible : public BooleanRewrapNegative< Detail::TypeTraits::IsTriviallyConstructible< T, TArgs... > > {};

} // namespace TypeTraits

} // namespace BR