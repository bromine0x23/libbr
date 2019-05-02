/**
 * @file
 * @brief 添加 \em volatile 修饰
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief 添加 \em volatile 修饰
 * @tparam T
 * @see Utility::TypeWrapper
 * @see AddVolatile
 *
 * 包装 \em T 添加 \em volatile 修饰后的类型
 */
template< typename T >
struct TypeAddVolatile;

/**
 * @brief TypeAddVolatile 的简写版本
 * @see TypeAddVolatile
 */
template< typename T >
using AddVolatile = TypeUnwrap< TypeAddVolatile<T> >;

} // namespace TypeTransform



namespace _ {
namespace TypeTransform {

template< typename T >
struct TypeAddVolatile : public TypeWrapper< T volatile > {
};

} // namespace TypeTransform
} // namespace _

inline namespace TypeTransform {

template< typename T >
struct TypeAddVolatile : public TypeRewrap< _::TypeTransform::TypeAddVolatile<T> > {};

} // namespace TypeTransform

} // namespace BR
