/**
 * @file
 * @brief 添加 \em const \em volatile 修饰
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
struct TypeAddConstVolatile : TypeWrapper< T const volatile > {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 添加 \em const \em volatile 修饰
 * @tparam T
 * @see TypeWrapper
 * @see AddConstVolatile
 *
 * 包装 \em T 添加 \em const \em volatile 修饰后的类型
 */
template< typename T >
struct TypeAddConstVolatile : TypeRewrap< Detail::TypeOperate::TypeAddConstVolatile<T> > {};

/**
 * @brief TypeAddConstVolatile 的简写版本
 * @tparam T
 * @see TypeAddConstVolatile
 */
template< typename T >
using AddConstVolatile = TypeUnwrap< TypeAddConstVolatile<T> >;

} // namespace BR
