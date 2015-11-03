/**
 * @file
 * @brief 移除指针修饰
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

/**
 * @brief 移除指针修饰
 * @tparam T
 * @see TypeWrapper
 * @see RemovePointer
 *
 * 包装 \em T 顶层指针修饰(如果存在)后的类型
 */
template< typename T >
struct TypeRemovePointer;

/**
 * @brief TypeRemovePointer 的简写版本
 * @tparam T
 * @see TypeRemovePointer
 */
template< typename T >
using RemovePointer = TypeUnwrap< TypeRemovePointer<T> >;

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeRemovePointer : public TypeWrapper<T> {
};

template< typename T >
struct TypeRemovePointer< T * > : public TypeWrapper<T> {
};

template< typename T >
struct TypeRemovePointer< T * const > : public TypeWrapper<T> {
};

template< typename T >
struct TypeRemovePointer< T * volatile > : public TypeWrapper<T> {
};

template< typename T >
struct TypeRemovePointer< T * const volatile > : public TypeWrapper<T> {
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct TypeRemovePointer : public TypeRewrap< Detail::TypeOperate::TypeRemovePointer<T> > {
};

} // namespace BR

