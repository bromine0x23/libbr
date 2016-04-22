/**
 * @file
 * @brief 算术类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_floating_point.hpp>

namespace BR {


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
struct IsArithmetic;

/**
 * @brief IsArithmetic 的否定
 * @tparam T 待检查类型
 * @see IsArithmetic
 */
template< typename T >
struct NotArithmetic;

#if defined(BR_CXX14)

/**
 * @brief IsArithmetic 的模板变量版本
 * @tparam T 待检查类型
 * @see IsArithmetic
 * @see not_arithmetic
 */
template< typename T >
constexpr auto is_arithmetic = bool_constant< IsArithmetic<T> >;

/**
 * @brief NotArithmetic 的模板变量版本
 * @tparam T 待检查类型
 * @see NotArithmetic
 * @see is_arithmetic
 */
template< typename T >
constexpr auto not_arithmetic = bool_constant< NotArithmetic<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

template< typename T >
using IsArithmetic = BooleanOr< IsIntegral<T>, IsFloatingPoint<T> >;

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct IsArithmetic : BooleanRewrapPositive< Detail::TypeTraits::IsArithmetic<T> > {};

template< typename T >
struct NotArithmetic : BooleanRewrapNegative< Detail::TypeTraits::IsArithmetic<T> > {};

} // namespace BR

