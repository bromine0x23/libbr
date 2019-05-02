/**
 * @file
 * @brief 添加右值引用修饰
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief 添加右值引用修饰
 * @tparam T
 * @see Utility::TypeWrapper
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

} // namespace TypeTransform



namespace _ {
namespace TypeTransform {

template< typename T >
struct TypeAddRValueReference : public TypeWrapper< T && > {};

template<>
struct TypeAddRValueReference< void > : public TypeWrapper< void > {};

template<>
struct TypeAddRValueReference< void const > : public TypeWrapper< void const > {};

template<>
struct TypeAddRValueReference< void volatile > : public TypeWrapper< void volatile > {};

template<>
struct TypeAddRValueReference< void const volatile > : public TypeWrapper< void const volatile > {};

} // namespace TypeTransform
} // namespace _

inline namespace TypeTransform {

template< typename T >
struct TypeAddRValueReference : public TypeRewrap< _::TypeTransform::TypeAddRValueReference<T> > {};

} // namespace TypeTransform


} // namespace BR