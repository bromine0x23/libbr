/**
 * @file
 * @brief 添加指针修饰
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>
#include <libbr/type_traits/remove_reference.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 添加指针修饰
 * @tparam T
 * @see TypeWrapper
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

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct TypeAddPointer : public TypeWrapper< RemoveReference<T> * > {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct TypeAddPointer : public TypeRewrap< Detail::TypeTraits::TypeAddPointer<T> > {};

} // namespace TypeTraits

} // namespace BR
