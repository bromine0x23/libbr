/**
 * @file
 * @brief 移除引用修饰
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

/**
 * @brief 移除引用修饰
 * @tparam T
 * @see TypeWrapper
 * @see RemoveReference
 *
 * 包装 \em T 顶层引用修饰(如果存在)后的类型
 */
template< typename T >
struct TypeRemoveReference;

/**
 * @brief TypeRemoveReference 的简写版本
 * @tparam T
 * @see TypeRemoveReference
 */
template< typename T >
using RemoveReference = TypeUnwrap< TypeRemoveReference<T> >;

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeRemoveReference : public TypeWrapper<T> {
};

template< typename T >
struct TypeRemoveReference< T & > : public TypeWrapper<T> {
};

template< typename T >
struct TypeRemoveReference< T && > : public TypeWrapper<T> {
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct TypeRemoveReference : public TypeRewrap< Detail::TypeOperate::TypeRemoveReference<T> > {
};

} // namespace BR