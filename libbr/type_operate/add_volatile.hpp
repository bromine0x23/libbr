/**
 * @file
 * @brief 添加 \em volatile 修饰符
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

/**
 * @brief 类型包装器 T -> T volatile
 */
template< typename T >
struct TypeAddVolatile : TypeWrapper< T volatile > {};

/**
 * @brief T -> T volatile
 */
template< typename T >
using AddVolatile = TypeUnwrap< TypeAddVolatile<T> >;

} // namespace BR
