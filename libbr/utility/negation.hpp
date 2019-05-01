/**
 * @file
 * @brief Negation - 逻辑否定
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 逻辑否定
 * @tparam TB
 * @see negation
 */
template< typename TB >
using Negation = BooleanRewrapNegative<TB>;

/**
 * @brief Negation 的模板变量版本
 * @tparam TB
 * @see Negation
 */
template< typename TB >
constexpr auto negation = boolean_constant< Negation<TB> >;

} // namespace Utility

} // namespace BR
