/**
 * @file
 * @brief 检查是否具有拷贝构造函数
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_constructible.hpp>
#include <libbr/type_transform/add_const.hpp>
#include <libbr/type_transform/add_lvalue_reference.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有拷贝构造函数
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsConstructible
 * @see NoCopyConstructor
 *
 * 如果 \em T 具有拷贝构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasCopyConstructor;

/**
 * @brief HasCopyConstructor 的否定
 * @tparam T 待检查类型
 * @see HasCopyConstructor
 */
template< typename T >
struct NoCopyConstructor;

/**
 * @brief HasCopyConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see HasCopyConstructor
 * @see no_copy_constructor
 */
template< typename T >
constexpr auto has_copy_constructor = boolean_constant< HasCopyConstructor<T> >;

/**
 * @brief NoCopyConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see NoCopyConstructor
 * @see has_copy_constructor
 */
template< typename T >
constexpr auto no_copy_constructor = boolean_constant< NoCopyConstructor<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
using HasCopyConstructor = IsConstructible< T, AddLValueReference< AddConst<T> > >;

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct HasCopyConstructor : public BooleanRewrapPositive< _::TypeTraits::HasCopyConstructor<T> > {};

template< typename T >
struct NoCopyConstructor : public BooleanRewrapNegative< _::TypeTraits::HasCopyConstructor<T> > {};

} // namespace TypeTraits

} // namespace BR