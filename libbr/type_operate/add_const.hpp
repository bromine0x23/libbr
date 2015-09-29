/**
 * @file
 * @brief 添加 \em const 修饰符
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

/**
 * @brief 类型包装器 T -> T const
 */
template< typename T >
struct TypeAddConst : TypeWrapper< T const > {};

/**
 * @brief T -> T const
 */
template< typename T >
using AddConst = TypeUnwrap< TypeAddConst< T > >;

} // namespace BR
