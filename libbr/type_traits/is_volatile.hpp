/**
 * @file
 * @brief \em volatile 修饰检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否包含 \em volatile 修饰
 * @tparam T 待检查类型
 * @see IntegerConstant
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

#if defined(BR_CXX14)

/**
 * @brief IsVolatile 的模板变量版本
 * @tparam T 待检查类型
 * @see is_volatile
 * @see not_volatile
 */
template< typename T >
constexpr auto is_volatile = bool_constant< IsVolatile<T> >;

/**
 * @brief NotVolatile 的模板变量版本
 * @tparam T 待检查类型
 * @see NotVolatile
 * @see is_volatile
 */
template< typename T >
constexpr auto not_volatile = bool_constant< NotVolatile<T> >;

#endif // defined(BR_CXX14)

namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsVolatile : public BooleanFalse {};

template< typename T >
struct IsVolatile< T volatile > : public BooleanTrue {};

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct IsVolatile : public BooleanRewrapPositive< Detail::TypeTraits::IsVolatile<T> > {};

template< typename T >
struct NotVolatile : public BooleanRewrapNegative< Detail::TypeTraits::IsVolatile<T> > {};

} // namespace BR