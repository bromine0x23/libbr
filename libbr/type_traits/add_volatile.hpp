/**
 * @file
 * @brief 添加 \em volatile 修饰
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 添加 \em volatile 修饰
 * @tparam T
 * @see TypeWrapper
 * @see AddVolatile
 *
 * 包装 \em T 添加 \em volatile 修饰后的类型
 */
template< typename T >
struct TypeAddVolatile;

/**
 * @brief TypeAddVolatile 的简写版本
 * @tparam T
 * @see TypeAddVolatile
 */
template< typename T >
using AddVolatile = TypeUnwrap< TypeAddVolatile<T> >;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct TypeAddVolatile : public TypeWrapper< T volatile > {
};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct TypeAddVolatile : public TypeRewrap< Detail::TypeTraits::TypeAddVolatile<T> > {};

} // namespace TypeTraits

} // namespace BR
