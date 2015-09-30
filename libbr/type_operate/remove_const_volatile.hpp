/**
 * @file
 * @brief 移除 \em const 和 \em volatile 修饰
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
struct TypeRemoveConstVolatile : TypeWrapper<T> {};

template< typename T >
struct TypeRemoveConstVolatile< T const > : TypeWrapper<T> {};

template< typename T >
struct TypeRemoveConstVolatile< T volatile > : TypeWrapper<T> {};

template< typename T >
struct TypeRemoveConstVolatile< T const volatile > : TypeWrapper<T> {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 移除 \em const 和 \em volatile 修饰
 * @tparam T
 * @see TypeWrapper
 * @see RemoveConstVolatile
 *
 * 包装 \em T 移除顶层的 \em const 和 \em volatile 修饰(如果存在)后的类型
 */
template< typename T >
struct TypeRemoveConst : TypeRewrap< Detail::TypeOperate::TypeRemoveConstVolatile<T> > {};

/**
 * @brief TypeRemoveConstVolatile 的简写版本
 * @tparam T
 * @see TypeRemoveConstVolatile
 */
template< typename T >
using RemoveConstVolatile = TypeUnwrap< TypeRemoveConstVolatile<T> >;

} // namespace BR