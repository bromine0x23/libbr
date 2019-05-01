/**
 * @file
 * @brief 添加 \em const 修饰
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

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

} // namespace TypeTransform



namespace _ {
namespace TypeTransform {

template< typename T >
struct TypeAddConst : public TypeWrapper< T const > {};

} // namespace TypeTransform
} // namespace _

inline namespace TypeTransform {

template< typename T >
struct TypeAddConst : public TypeRewrap< _::TypeTransform::TypeAddConst<T> > {};

} // namespace TypeTransform

} // namespace BR
