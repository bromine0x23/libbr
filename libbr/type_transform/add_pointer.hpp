/**
 * @file
 * @brief 添加指针修饰
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_transform/remove_reference.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief 添加指针修饰
 * @tparam T
 * @see Utility::TypeWrapper
 * @see AddPointer
 *
 * 包装 \em T 添加指针修饰(<tt>T *</tt>)后的类型
 */
template< typename T >
struct TypeAddPointer;

/**
 * @brief TypeAddPointer 的简写版本
 * @tparam T
 * @see TypeAddPointer
 */
template< typename T >
using AddPointer = TypeUnwrap< TypeAddPointer<T> >;

} // namespace TypeTransform



namespace _::TypeTransform {

template< typename T >
struct TypeAddPointer : public TypeWrapper< RemoveReference<T> * > {};

} // namespace _::TypeTransform

inline namespace TypeTransform {

template< typename T >
struct TypeAddPointer : public TypeRewrap< _::TypeTransform::TypeAddPointer<T> > {};

} // namespace TypeTransform

} // namespace BR
