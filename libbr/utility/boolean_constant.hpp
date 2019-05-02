/**
 * @file
 * @brief BooleanConstant - 布尔常量类型
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 布尔常量封装类
 */
template< Boolean value >
using BooleanConstant = IntegralConstant< Boolean, value >;

/**
 * @brief 封装布尔常量true
 */
using BooleanTrue = BooleanConstant<true>;

/**
 * @brief 封装布尔常量false
 */
using BooleanFalse = BooleanConstant<false>;

template< typename TB >
using BooleanRewrapPositive = BooleanConstant< !!TB::value > ;

template< typename TB >
using BooleanRewrapNegative = BooleanConstant< !TB::value > ;

template< typename TConstant >
using BooleanRewrap = BooleanRewrapPositive< TConstant >;

/**
 * @brief 布尔常量解包
 * @tparam TConstant
 */
template< typename TConstant >
constexpr Boolean boolean_constant = integral_constant<TConstant>;

} // namespace Utility

} // namespace BR
