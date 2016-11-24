/**
 * @file
 * @brief 移除数组的所有维度
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 移除数组的所有维度
 * @tparam T
 * @see TypeWrapper
 * @see RemoveAllExtents
 *
 * 如果 \em T 是 \em U 的任意维度的数组类型，则包装的类型为 \em U ；否则为 \em T
 */
template< typename T >
struct TypeRemoveAllExtents;

/**
 * @brief TypeRemoveAllExtents 的简写版本
 * @tparam T
 * @see TypeRemoveAllExtents
 */
template< typename T >
using RemoveAllExtents = TypeUnwrap< TypeRemoveAllExtents<T> >;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct TypeRemoveAllExtents : public TypeWrapper<T> {
};

template< typename T >
struct TypeRemoveAllExtents< T[] > : public TypeRemoveAllExtents<T> {
};

template< typename T, Size S >
struct TypeRemoveAllExtents< T[S] > : public TypeRemoveAllExtents<T> {
};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct TypeRemoveAllExtents : public TypeRewrap< Detail::TypeTraits::TypeRemoveAllExtents<T> > {};

} // namespace TypeTraits

} // namespace BR



