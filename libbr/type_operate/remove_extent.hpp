/**
 * @file
 * @brief 移除数组的一个维度
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeRemoveExtent : TypeWrapper<T> {};

template< typename T >
struct TypeRemoveExtent< T [] > : TypeWrapper<T> {};

template< typename T, Size S >
struct TypeRemoveExtent< T [S] > : TypeWrapper<T> {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 移除数组的一个维度
 * @tparam T
 * @see TypeWrapper
 * @see RemoveExtent
 *
 * 如果 \em T 是 \em U 的一维数组类型(<tt>U[]</tt>、<tt>U[S]</tt>)，则包装的类型为 \em U ；否则为 \em T
 */
template< typename T >
struct TypeRemoveExtent : TypeRewrap< Detail::TypeOperate::TypeRemoveExtent<T> > {};

/**
 * @brief TypeRemoveExtent 的简写版本
 * @tparam T
 * @see TypeRemoveExtent
 */
template< typename T >
using RemoveExtent = TypeUnwrap< TypeRemoveExtent<T> >;

} // namespace BR


