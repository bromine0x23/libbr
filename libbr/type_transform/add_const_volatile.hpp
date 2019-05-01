/**
 * @file
 * @brief 添加 \em const \em volatile 修饰
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief 添加 \em const \em volatile 修饰
 * @tparam T
 * @see TypeWrapper
 * @see AddConstVolatile
 *
 * 包装 \em T 添加 \em const \em volatile 修饰后的类型
 */
template< typename T >
struct TypeAddConstVolatile;

/**
 * @brief TypeAddConstVolatile 的简写版本
 * @tparam T
 * @see TypeAddConstVolatile
 */
template< typename T >
using AddConstVolatile = TypeUnwrap< TypeAddConstVolatile<T> >;

} // namespace TypeTransform



namespace _ {
namespace TypeTransform {

template< typename T >
struct TypeAddConstVolatile : public TypeWrapper< T const volatile > {
};

} // namespace TypeTransform
} // namespace _

inline namespace TypeTransform {

template< typename T >
struct TypeAddConstVolatile : public TypeRewrap< _::TypeTransform::TypeAddConstVolatile<T> > {};

} // namespace TypeTransform

} // namespace BR
