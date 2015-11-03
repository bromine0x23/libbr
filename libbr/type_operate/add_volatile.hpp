/**
 * @file
 * @brief 添加 \em volatile 修饰
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

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

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeAddVolatile : public TypeWrapper< T volatile > {
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct TypeAddVolatile : public TypeRewrap< Detail::TypeOperate::TypeAddVolatile<T> > {
};

} // namespace BR
