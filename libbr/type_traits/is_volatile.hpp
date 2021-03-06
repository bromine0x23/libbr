/**
 * @file
 * @brief \em volatile 修饰检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否包含 \em volatile 修饰
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see NotVolatile
 *
 * 如果 \em T 包含顶层 \em volatile 修饰，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsVolatile;

/**
 * @brief IsVolatile 的否定
 * @tparam T 待检查类型
 * @see IsVolatile
 */
template< typename T >
struct NotVolatile;

/**
 * @brief IsVolatile 的模板变量版本
 * @tparam T 待检查类型
 * @see is_volatile
 * @see not_volatile
 */
template< typename T >
constexpr auto is_volatile = boolean_constant< IsVolatile<T> >;

/**
 * @brief NotVolatile 的模板变量版本
 * @tparam T 待检查类型
 * @see NotVolatile
 * @see is_volatile
 */
template< typename T >
constexpr auto not_volatile = boolean_constant< NotVolatile<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
struct IsVolatile : public BooleanFalse {};

template< typename T >
struct IsVolatile< T volatile > : public BooleanTrue {};

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct IsVolatile : public BooleanRewrapPositive< _::TypeTraits::IsVolatile<T> > {};

template< typename T >
struct NotVolatile : public BooleanRewrapNegative< _::TypeTraits::IsVolatile<T> > {};

} // namespace TypeTraits

} // namespace BR