/**
 * @file
 * @brief 移除 \em volatile 修饰
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief 移除 \em volatile 修饰
 * @tparam T
 * @see Utility::TypeWrapper
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

} // namespace TypeTransform



namespace _ {
namespace TypeTransform {

template< typename T >
struct TypeRemoveVolatile : public TypeWrapper<T> {};

template< typename T >
struct TypeRemoveVolatile< T volatile > : public TypeWrapper<T> {};

} // namespace TypeTransform
} // namespace _

inline namespace TypeTransform {

template< typename T >
struct TypeRemoveVolatile : public TypeRewrap< _::TypeTransform::TypeRemoveVolatile<T> > {};

} // namespace TypeTransform

} // namespace BR