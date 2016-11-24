/**
 * @file
 * @brief 添加 \em const 修饰
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 添加 \em const 修饰
 * @tparam T
 * @see TypeWrapper
 * @see AddConst
 *
 * 包装 \em T 添加 \em const 修饰后的类型
 */
template< typename T >
struct TypeAddConst;

/**
 * @brief TypeAddConst 的简写版本
 * @tparam T
 * @see TypeAddConst
 */
template< typename T >
using AddConst = TypeUnwrap< TypeAddConst<T> >;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct TypeAddConst : public TypeWrapper< T const > {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct TypeAddConst : public TypeRewrap< Detail::TypeTraits::TypeAddConst<T> > {};

} // namespace TypeTraits

} // namespace BR
