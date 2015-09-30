/**
 * @file
 * @brief 移除 \em const 修饰
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
struct TypeRemoveConst : TypeWrapper<T> {};

template< typename T >
struct TypeRemoveConst< T const > : TypeWrapper<T> {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 移除 \em const 修饰
 * @tparam T
 * @see TypeWrapper
 * @see RemoveConst
 *
 * 包装 \em T 移除顶层的 \em const 修饰(如果存在)后的类型
 */
template< typename T >
struct TypeRemoveConst : TypeRewrap< Detail::TypeOperate::TypeRemoveConst<T> > {};

/**
 * @brief TypeRemoveConst 的简写版本
 * @tparam T
 * @see TypeRemoveConst
 */
template< typename T >
using RemoveConst = TypeUnwrap< TypeRemoveConst<T> >;

} // namespace BR
