/**
 * @file
 * @brief 移除 \em const 修饰
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 移除 \em const 修饰
 * @tparam T
 * @see TypeWrapper
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

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct TypeRemoveConst : public TypeWrapper<T> {};

template< typename T >
struct TypeRemoveConst< T const > : public TypeWrapper<T> {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct TypeRemoveConst : public TypeRewrap< Detail::TypeTraits::TypeRemoveConst<T> > {};

} // namespace TypeTraits

} // namespace BR
