/**
 * @file
 * @brief 移除数组的一个维度
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief 移除数组的一个维度
 * @tparam T
 * @see Utility::TypeWrapper
 * @see RemoveExtent
 *
 * 如果 \em T 是 \em U 的一维数组类型(<tt>U[]</tt>、<tt>U[S]</tt>)，则包装的类型为 \em U ；否则为 \em T
 */
template< typename T >
struct TypeRemoveExtent;

/**
 * @brief TypeRemoveExtent 的简写版本
 * @tparam T
 * @see TypeRemoveExtent
 */
template< typename T >
using RemoveExtent = TypeUnwrap< TypeRemoveExtent<T> >;

} // namespace TypeTransform



namespace _ {
namespace TypeTransform {

template< typename T >
struct TypeRemoveExtent : public TypeWrapper<T> {};

template< typename T >
struct TypeRemoveExtent< T[] > : public TypeWrapper<T> {};

template< typename T, Size S >
struct TypeRemoveExtent< T[S] > : public TypeWrapper<T> {};

} // namespace TypeTransform
} // namespace _

inline namespace TypeTransform {

template< typename T >
struct TypeRemoveExtent : public TypeRewrap< _::TypeTransform::TypeRemoveExtent<T> > {};

} // namespace TypeTransform

} // namespace BR


