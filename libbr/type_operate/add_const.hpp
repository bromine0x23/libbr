/**
 * @file
 * @brief 添加 \em const 修饰
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
struct TypeAddConst : TypeWrapper< T const > {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 添加 \em const 修饰
 * @tparam T
 * @see TypeWrapper
 * @see AddConst
 *
 * 包装 \em T 添加 \em const 修饰后的类型
 */
template< typename T >
struct TypeAddConst : TypeRewrap< Detail::TypeOperate::TypeAddConst<T> > {};

/**
 * @brief TypeAddConst 的简写版本
 * @tparam T
 * @see TypeAddConst
 */
template< typename T >
using AddConst = TypeUnwrap< TypeAddConst< T > >;

} // namespace BR
