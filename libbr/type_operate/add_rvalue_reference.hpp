/**
 * @file
 * @brief 添加右值引用修饰符
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

/**
 * @brief 类型包装器 T -> T &&
 */
template< typename T >
struct TypeAddRValueReference : TypeWrapper< T && > {};

template<>
struct TypeAddRValueReference<void > : TypeWrapper<void> {};

/**
 * @brief T -> T &&
 */
template< typename T >
using AddRValueReference = TypeUnwrap< TypeAddRValueReference<T> >;

} // namespace BR