/**
 * @file
 * @brief 移除指针修饰
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

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

} // namespace TypeTransform



namespace _ {
namespace TypeTransform {

template< typename T >
struct TypeRemovePointer : public TypeWrapper<T> {};

template< typename T >
struct TypeRemovePointer< T * > : public TypeWrapper<T> {};

template< typename T >
struct TypeRemovePointer< T * const > : public TypeWrapper<T> {};

template< typename T >
struct TypeRemovePointer< T * volatile > : public TypeWrapper<T> {};

template< typename T >
struct TypeRemovePointer< T * const volatile > : public TypeWrapper<T> {};

} // namespace TypeTransform
} // namespace _

inline namespace TypeTransform {

template< typename T >
struct TypeRemovePointer : public TypeRewrap< _::TypeTransform::TypeRemovePointer<T> > {};

} // namespace TypeTransform

} // namespace BR

