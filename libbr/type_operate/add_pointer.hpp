/**
 * @file
 * @brief 添加指针修饰符
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/remove_reference.hpp>

namespace BR {

/**
 * @brief 类型包装器 T -> T *
 */
template< typename T >
struct TypeAddPointer : TypeWrapper< RemoveReference<T> * > {};

/**
 * @brief T -> T *
 */
template< typename T >
using AddPointer = TypeUnwrap< TypeAddPointer<T> >;

} // namespace BR
