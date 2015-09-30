/**
 * @file
 * @brief \em volatile 修饰检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsVolatile : BooleanFalse {};

template< typename T >
struct IsVolatile< T volatile > : BooleanTrue {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否包含 \em volatile 修饰
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotVolatile
 *
 * 如果 \em T 包含顶层 \em volatile 修饰，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsVolatile : Boolean< Detail::TypeOperate::IsVolatile<T> > {};

/**
 * @brief IsVolatile 的否定
 * @tparam T 待检查类型
 * @see IsVolatile
 */
template< typename T >
struct NotVolatile : BooleanNot< Detail::TypeOperate::IsVolatile<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsVolatile 的模板变量版本
 * @tparam T 待检查类型
 * @see is_volatile
 * @see not_volatile
 */
template< typename T >
constexpr auto is_volatile = IsVolatile<T>::value;

/**
 * @brief NotVolatile 的模板变量版本
 * @tparam T 待检查类型
 * @see NotVolatile
 * @see is_volatile
 */
template< typename T >
constexpr auto not_volatile = NotVolatile<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR