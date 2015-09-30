/**
 * @file
 * @brief 移除指针修饰
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeRemovePointerBasic : TypeWrapper<T> {};

template< typename T >
struct TypeRemovePointerBasic< T * > : TypeWrapper<T> {};

template< typename T >
using TypeRemovePointer = TypeRemovePointerBasic< RemoveConstVolatile<T> >;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 移除指针修饰
 * @tparam T
 * @see TypeWrapper
 * @see RemovePointer
 *
 * 包装 \em T 顶层指针修饰(如果存在)后的类型
 */
template< typename T >
struct TypeRemovePointer : TypeRewrap< Detail::TypeOperate::TypeRemovePointer<T> > {};

/**
 * @brief TypeRemovePointer 的简写版本
 * @tparam T
 * @see TypeRemovePointer
 */
template< typename T >
using RemovePointer = TypeUnwrap< TypeRemovePointer<T> >;

} // namespace BR

