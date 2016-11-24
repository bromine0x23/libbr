/**
 * @file
 * @brief 添加右值引用修饰
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

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

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

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

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct TypeAddRValueReference : public TypeRewrap< Detail::TypeTraits::TypeAddRValueReference<T> > {};

} // namespace TypeTraits


} // namespace BR