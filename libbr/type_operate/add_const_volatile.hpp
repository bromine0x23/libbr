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

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeAddConstVolatile : public TypeWrapper< T const volatile > {
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct TypeAddConstVolatile : public TypeRewrap< Detail::TypeOperate::TypeAddConstVolatile<T> > {
};

} // namespace BR
