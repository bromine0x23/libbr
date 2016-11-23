/**
 * @file
 * @brief 移除指针修饰
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

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

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

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

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct TypeRemovePointer : public TypeRewrap< Detail::TypeTraits::TypeRemovePointer<T> > {};

} // namespace TypeTraits

} // namespace BR

