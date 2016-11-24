/**
 * @file
 * @brief 移除 \em const 和 \em volatile 修饰
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 移除 \em const 和 \em volatile 修饰
 * @tparam T
 * @see TypeWrapper
 * @see RemoveConstVolatile
 *
 * 包装 \em T 移除顶层的 \em const 和 \em volatile 修饰(如果存在)后的类型
 */
template< typename T >
struct TypeRemoveConstVolatile;

/**
 * @brief TypeRemoveConstVolatile 的简写版本
 * @tparam T
 * @see TypeRemoveConstVolatile
 */
template< typename T >
using RemoveConstVolatile = TypeUnwrap< TypeRemoveConstVolatile<T> >;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct TypeRemoveConstVolatile : public TypeWrapper<T> {};

template< typename T >
struct TypeRemoveConstVolatile< T const > : public TypeWrapper<T> {};

template< typename T >
struct TypeRemoveConstVolatile< T volatile > : public TypeWrapper<T> {};

template< typename T >
struct TypeRemoveConstVolatile< T const volatile > : public TypeWrapper<T> {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct TypeRemoveConstVolatile : public TypeRewrap< Detail::TypeTraits::TypeRemoveConstVolatile<T> > {};

} // namespace TypeTraits

} // namespace BR