/**
 * @file
 * @brief 添加 \em const \em volatile 修饰符
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

/**
 * @brief 类型包装器 T -> T const volatile
 */
template< typename T >
struct TypeAddConstVolatile : TypeWrapper< T const volatile > {};

/**
 * @brief T -> T const volatile
 */
template< typename T >
using AddConstVolatile = TypeUnwrap< TypeAddConstVolatile< T > >;

} // namespace BR
