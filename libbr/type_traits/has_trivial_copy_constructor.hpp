/**
 * @file
 * @brief 检查是否具有平凡的拷贝构造函数
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_trivially_constructible.hpp>
#include <libbr/type_transform/add_const.hpp>
#include <libbr/type_transform/add_lvalue_reference.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有平凡的拷贝构造函数
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsTriviallyConstructible
 * @see HasCopyConstructor
 * @see NoTrivialCopyConstructor
 *
 * 如果 \em T 具有平凡的拷贝构造函数，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasTrivialCopyConstructor;

/**
 * @brief HasTrivialCopyConstructor 的否定
 * @tparam T 待检查类型
 * @see HasTrivialCopyConstructor
 */
template< typename T >
struct NoTrivialCopyConstructor;

/**
 * @brief HasTrivialCopyConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see HasTrivialCopyConstructor
 * @see no_trivial_copy_constructor
 */
template< typename T >
constexpr auto has_trivial_copy_constructor = boolean_constant< HasTrivialCopyConstructor<T> >;

/**
 * @brief NoTrivialCopyConstructor 的模板变量版本
 * @tparam T 待检查类型
 * @see NoTrivialCopyConstructor
 * @see has_trivial_copy_constructor
 */
template< typename T >
constexpr auto no_trivial_copy_constructor = boolean_constant< NoTrivialCopyConstructor<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
using HasTrivialCopyConstructor = IsTriviallyConstructible< T, AddLValueReference< AddConst<T> > >;

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct HasTrivialCopyConstructor : public BooleanRewrapPositive< _::TypeTraits::HasTrivialCopyConstructor<T> > {};

template< typename T >
struct NoTrivialCopyConstructor : public BooleanRewrapNegative< _::TypeTraits::HasTrivialCopyConstructor<T> > {};

} // namespace TypeTraits

} // namespace BR