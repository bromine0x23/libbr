/**
 * @file
 * @brief 布尔常量类型
 * @author Bromine0x23
 * @since 2015/6/23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integer_constant.hpp>

namespace BR {

/**
 * @brief 布尔常量封装类
 */
template< bool value >
using BooleanConstant = IntegerConstant< bool, value >;

/**
 * @brief 封装布尔常量true
 */
using BooleanTrue = BooleanConstant<true>;

/**
 * @brief 封装布尔常量false
 */
using BooleanFalse = BooleanConstant<false>;

#if defined(BR_CXX14)

template< typename TB >
constexpr static bool bool_constant = integer_constant<TB>;

#endif // defined(BR_CXX14)

} // namespace BR
