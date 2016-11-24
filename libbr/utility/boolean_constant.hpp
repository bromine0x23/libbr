/**
 * @file
 * @brief 布尔常量类型
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

/**
 * @brief 布尔常量封装类
 */
template< bool value >
using BooleanConstant = IntegralConstant< bool, value >;

/**
 * @brief 封装布尔常量true
 */
using BooleanTrue = BooleanConstant<true>;

/**
 * @brief 封装布尔常量false
 */
using BooleanFalse = BooleanConstant<false>;

template< typename TB >
using BooleanRewrapPositive = BooleanConstant< !!(TB{}) > ;

template< typename TB >
using BooleanRewrapNegative = BooleanConstant< !(TB{}) > ;

template< typename TB >
using BooleanRewrap = BooleanRewrapPositive< TB >;

#if defined(BR_CXX14)

/**
 * @brief boolean_constant
 * @tparam TB
 */
template< typename TB >
constexpr static bool boolean_constant = integral_constant<TB>;

#endif // defined(BR_CXX14)

} // namespace BR
