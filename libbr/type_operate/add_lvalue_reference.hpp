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

/**
 * @brief 添加左值引用修饰
 * @tparam T
 * @see TypeWrapper
 * @see AddLValueReference
 *
 * 包装 \em T 添加左值引用修饰(<tt>T &</tt>)后的类型
 */
template< typename T >
struct TypeAddLValueReference;

/**
 * @brief TypeAddLValueReference 的简写版本
 * @tparam T
 * @see TypeAddLValueReference
 */
template< typename T >
using AddLValueReference = TypeUnwrap< TypeAddLValueReference<T> >;

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeAddLValueReference : public TypeWrapper< T & > {
};

template<>
struct TypeAddLValueReference< void > : public TypeWrapper< void > {
};

template<>
struct TypeAddLValueReference< void const > : public TypeWrapper< void const > {
};

template<>
struct TypeAddLValueReference< void volatile > : public TypeWrapper< void volatile > {
};

template<>
struct TypeAddLValueReference< void const volatile > : TypeWrapper< void const volatile > {
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct TypeAddLValueReference : public TypeRewrap< Detail::TypeOperate::TypeAddLValueReference<T> > {
};

} // namespace BR