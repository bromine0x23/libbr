/**
 * @file
 * @brief 添加右值引用修饰
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
struct TypeAddRValueReference : TypeWrapper< T && > {};

template<>
struct TypeAddRValueReference<void > : TypeWrapper<void> {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 添加右值引用修饰
 * @tparam T
 * @see TypeWrapper
 * @see AddRValueReference
 *
 * 包装 \em T 添加右值引用修饰(<tt>T &&</tt>)后的类型
 */
template< typename T >
struct TypeAddRValueReference : TypeRewrap< Detail::TypeOperate::TypeAddRValueReference<T> > {};

/**
 * @brief TypeAddRValueReference 的简写版本
 * @tparam T
 * @see TypeAddRValueReference
 */
template< typename T >
using AddRValueReference = TypeUnwrap< TypeAddRValueReference<T> >;

} // namespace BR