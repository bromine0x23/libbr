/**
 * @file
 * @brief 移除 \em volatile 修饰
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 移除 \em volatile 修饰
 * @tparam T
 * @see TypeWrapper
 * @see RemoveVolatile
 *
 * 包装 \em T 移除顶层的 \em volatile 修饰(如果存在)后的类型
 */
template< typename T >
struct TypeRemoveVolatile;

/**
 * @brief TypeRemoveVolatile 的简写版本
 * @tparam T
 * @see TypeRemoveVolatile
 */
template< typename T >
using RemoveVolatile = TypeUnwrap< TypeRemoveVolatile<T> >;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct TypeRemoveVolatile : public TypeWrapper<T> {};

template< typename T >
struct TypeRemoveVolatile< T volatile > : public TypeWrapper<T> {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct TypeRemoveVolatile : public TypeRewrap< Detail::TypeTraits::TypeRemoveVolatile<T> > {};

} // namespace TypeTraits

} // namespace BR