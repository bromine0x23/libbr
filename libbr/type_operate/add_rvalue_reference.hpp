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

/**
 * @brief 添加右值引用修饰
 * @tparam T
 * @see TypeWrapper
 * @see AddRValueReference
 *
 * 包装 \em T 添加右值引用修饰(<tt>T &&</tt>)后的类型
 */
template< typename T >
struct TypeAddRValueReference;

/**
 * @brief TypeAddRValueReference 的简写版本
 * @tparam T
 * @see TypeAddRValueReference
 */
template< typename T >
using AddRValueReference = TypeUnwrap< TypeAddRValueReference<T> >;

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeAddRValueReference : public TypeWrapper< T && > {
};

template<>
struct TypeAddRValueReference< void > : public TypeWrapper< void > {
};

template<>
struct TypeAddRValueReference< void const > : public TypeWrapper< void const > {
};

template<>
struct TypeAddRValueReference< void volatile > : public TypeWrapper< void volatile > {
};

template<>
struct TypeAddRValueReference< void const volatile > : public TypeWrapper< void const volatile > {
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct TypeAddRValueReference : public TypeRewrap< Detail::TypeOperate::TypeAddRValueReference<T> > {
};

} // namespace BR