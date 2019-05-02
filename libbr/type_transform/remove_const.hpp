/**
 * @file
 * @brief 移除 \em const 修饰
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief 移除 \em const 修饰
 * @tparam T
 * @see Utility::TypeWrapper
 * @see RemoveConst
 *
 * 包装 \em T 移除顶层的 \em const 修饰(如果存在)后的类型
 */
template< typename T >
struct TypeRemoveConst;

/**
 * @brief TypeRemoveConst 的简写版本
 * @tparam T
 * @see TypeRemoveConst
 */
template< typename T >
using RemoveConst = TypeUnwrap< TypeRemoveConst<T> >;

} // namespace TypeTransform



namespace _ {
namespace TypeTransform {

template< typename T >
struct TypeRemoveConst : public TypeWrapper<T> {};

template< typename T >
struct TypeRemoveConst< T const > : public TypeWrapper<T> {};

} // namespace TypeTransform
} // namespace _

inline namespace TypeTransform {

template< typename T >
struct TypeRemoveConst : public TypeRewrap< _::TypeTransform::TypeRemoveConst<T> > {};

} // namespace TypeTransform

} // namespace BR
