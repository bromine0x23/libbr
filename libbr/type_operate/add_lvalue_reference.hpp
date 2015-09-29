/**
 * @file
 * @brief 添加左值引用修饰符
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

/**
 * @brief 类型包装器 T -> T &
 */
template< typename T >
struct TypeAddLValueReference : TypeWrapper< T & > {};

template<>
struct TypeAddLValueReference<void> : TypeWrapper<void> {};

/**
 * @brief T -> T &
 */
template< typename T >
using AddLValueReference = TypeUnwrap< TypeAddLValueReference<T> >;

} // namespace BR