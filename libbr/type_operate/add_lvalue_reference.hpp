/**
 * @file
 * @brief 添加左值引用修饰
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
struct TypeAddLValueReference : TypeWrapper< T & > {};

template<>
struct TypeAddLValueReference<void> : TypeWrapper<void> {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 添加左值引用修饰
 * @tparam T
 * @see TypeWrapper
 * @see AddLValueReference
 *
 * 包装 \em T 添加左值引用修饰(<tt>T &</tt>)后的类型
 */
template< typename T >
struct TypeAddLValueReference : TypeRewrap< Detail::TypeOperate::TypeAddLValueReference<T> > {};

/**
 * @brief TypeAddLValueReference 的简写版本
 * @tparam T
 * @see TypeAddLValueReference
 */
template< typename T >
using AddLValueReference = TypeUnwrap< TypeAddLValueReference<T> >;

} // namespace BR