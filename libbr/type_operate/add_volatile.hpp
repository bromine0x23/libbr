/**
 * @file
 * @brief 添加 \em volatile 修饰
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeAddVolatile : TypeWrapper< T volatile > {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 添加 \em volatile 修饰
 * @tparam T
 * @see TypeWrapper
 * @see AddVolatile
 *
 * 包装 \em T 添加 \em volatile 修饰后的类型
 */
template< typename T >
struct TypeAddVolatile : TypeRewrap< Detail::TypeOperate::TypeAddVolatile<T> > {};

/**
 * @brief TypeAddVolatile 的简写版本
 * @tparam T
 * @see TypeAddVolatile
 */
template< typename T >
using AddVolatile = TypeUnwrap< TypeAddVolatile<T> >;

} // namespace BR
