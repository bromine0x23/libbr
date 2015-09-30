/**
 * @file
 * @brief 移除 \em volatile 修饰
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
struct TypeRemoveVolatile : TypeWrapper<T> {};

template< typename T >
struct TypeRemoveVolatile< T volatile > : TypeWrapper<T> {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 移除 \em volatile 修饰
 * @tparam T
 * @see TypeWrapper
 * @see RemoveVolatile
 *
 * 包装 \em T 移除顶层的 \em volatile 修饰(如果存在)后的类型
 */
template< typename T >
struct TypeRemoveVolatile : TypeRewrap< Detail::TypeOperate::TypeRemoveVolatile<T> > {};

/**
 * @brief TypeRemoveVolatile 的简写版本
 * @tparam T
 * @see TypeRemoveVolatile
 */
template< typename T >
using RemoveVolatile = TypeUnwrap< TypeRemoveVolatile< T > >;

} // namespace BR