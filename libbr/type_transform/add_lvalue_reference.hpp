/**
 * @file
 * @brief 添加左值引用修饰
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief 添加左值引用修饰
 * @tparam T
 * @see Utility::TypeWrapper
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

} // namespace TypeTransform



namespace _ {
namespace TypeTransform {

template< typename T >
struct TypeAddLValueReference : public TypeWrapper< T & > {};

template<>
struct TypeAddLValueReference< void > : public TypeWrapper< void > {};

template<>
struct TypeAddLValueReference< void const > : public TypeWrapper< void const > {};

template<>
struct TypeAddLValueReference< void volatile > : public TypeWrapper< void volatile > {};

template<>
struct TypeAddLValueReference< void const volatile > : TypeWrapper< void const volatile > {};

} // namespace TypeTransform
} // namespace _

inline namespace TypeTransform {

template< typename T >
struct TypeAddLValueReference : public TypeRewrap< _::TypeTransform::TypeAddLValueReference<T> > {};

} // namespace TypeTransform

} // namespace BR