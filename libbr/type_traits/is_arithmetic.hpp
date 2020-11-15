/**
 * @file
 * @brief 算术类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_floating_point.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/disjunction.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是算术类型
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsIntegral
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

/**
 * @brief IsArithmetic 的模板变量版本
 * @tparam T 待检查类型
 * @see IsArithmetic
 * @see not_arithmetic
 */
template< typename T >
constexpr auto is_arithmetic = boolean_constant< IsArithmetic<T> >;

/**
 * @brief NotArithmetic 的模板变量版本
 * @tparam T 待检查类型
 * @see NotArithmetic
 * @see is_arithmetic
 */
template< typename T >
constexpr auto not_arithmetic = boolean_constant< NotArithmetic<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
using IsArithmetic = Disjunction< IsIntegral<T>, IsFloatingPoint<T> >;

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct IsArithmetic : public BooleanRewrapPositive< _::TypeTraits::IsArithmetic<T> > {};

template< typename T >
struct NotArithmetic : public BooleanRewrapNegative< _::TypeTraits::IsArithmetic<T> > {};

} // namespace TypeTraits

} // namespace BR

