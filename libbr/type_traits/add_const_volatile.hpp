/**
 * @file
 * @brief 添加 \em const \em volatile 修饰
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

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

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct TypeAddConstVolatile : public TypeWrapper< T const volatile > {
};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct TypeAddConstVolatile : public TypeRewrap< Detail::TypeTraits::TypeAddConstVolatile<T> > {};

} // namespace TypeTraits

} // namespace BR
