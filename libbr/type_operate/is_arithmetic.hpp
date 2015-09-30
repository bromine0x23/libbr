/**
 * @file
 * @brief 算术类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_integer.hpp>
#include <libbr/type_operate/is_floating_point.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsArithmetic = BooleanOr< IsInteger<T>, IsFloatingPoint<T> >;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是算术类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsInteger
 * @see IsFloatingPoint
 * @see NotArithmetic
 *
 * 如果 \em T 是算术类型(整型类型或浮点类型)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsArithmetic : Boolean< Detail::TypeOperate::IsArithmetic<T> > {};

/**
 * @brief IsArithmetic 的否定
 * @tparam T 待检查类型
 * @see IsArithmetic
 */
template< typename T >
struct NotArithmetic : BooleanNot< Detail::TypeOperate::IsArithmetic<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsArithmetic 的模板变量版本
 * @tparam T 待检查类型
 * @see IsArithmetic
 * @see not_arithmetic
 */
template< typename T >
constexpr auto is_arithmetic = IsArithmetic<T>::value;

/**
 * @brief NotArithmetic 的模板变量版本
 * @tparam T 待检查类型
 * @see NotArithmetic
 * @see is_arithmetic
 */
template< typename T >
constexpr auto not_arithmetic = NotArithmetic<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR

