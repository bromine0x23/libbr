/**
 * @file
 * @brief 移除数组的所有维度
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeRemoveAllExtents : TypeWrapper<T> {};

template< typename T >
struct TypeRemoveAllExtents< T [] > : TypeRemoveAllExtents<T> {};

template< typename T, Size S >
struct TypeRemoveAllExtents< T [S] > : TypeRemoveAllExtents<T> {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 移除数组的所有维度
 * @tparam T
 * @see TypeWrapper
 * @see RemoveAllExtents
 *
 * 如果 \em T 是 \em U 的任意维度的数组类型，则包装的类型为 \em U ；否则为 \em T
 */
template< typename T >
struct TypeRemoveAllExtents : TypeRewrap< Detail::TypeOperate::TypeRemoveAllExtents<T> > {};

/**
 * @brief TypeRemoveAllExtents 的简写版本
 * @tparam T
 * @see TypeRemoveAllExtents
 */
template< typename T >
using RemoveAllExtents = TypeUnwrap< TypeRemoveAllExtents< T > >;

} // namespace BR



