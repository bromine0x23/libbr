/**
 * @file
 * @brief 移除引用修饰
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief 移除引用修饰
 * @tparam T
 * @see Utility::TypeWrapper
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

} // namespace TypeTransform



namespace _::TypeTransform {

template< typename T >
struct TypeRemoveReference : public TypeWrapper<T> {};

template< typename T >
struct TypeRemoveReference< T & > : public TypeWrapper<T> {};

template< typename T >
struct TypeRemoveReference< T && > : public TypeWrapper<T> {};

} // namespace _::TypeTransform

inline namespace TypeTransform {

template< typename T >
struct TypeRemoveReference : public TypeRewrap< _::TypeTransform::TypeRemoveReference<T> > {};

} // namespace TypeTransform

} // namespace BR