/**
 * @file
 * @brief 检查是否具有(复制)赋值运算符
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_transform/add_const.hpp>
#include <libbr/type_transform/add_lvalue_reference.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有(复制)赋值运算符
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsAssignable
 * @see NoCopyAssignment
 *
 * 如果 \em T 具有(复制)赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasCopyAssignment;

/**
 * @brief HasCopyAssignment 的否定
 * @tparam T 待检查类型
 * @see HasCopyAssignment
 */
template< typename T >
struct NoCopyAssignment;

/**
 * @brief HasCopyAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see HasCopyAssignment
 * @see no_copy_assignment
 */
template< typename T >
constexpr auto has_copy_assignment = boolean_constant< HasCopyAssignment<T> >;

/**
 * @brief NoCopyAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see NoCopyAssignment
 * @see has_copy_assignment
 */
template< typename T >
constexpr auto no_copy_assignment = boolean_constant< NoCopyAssignment<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
using HasCopyAssignment = IsAssignable< AddLValueReference<T>, AddLValueReference< AddConst<T> > >;

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct HasCopyAssignment : BooleanRewrapPositive< _::TypeTraits::HasCopyAssignment<T> > {};

template< typename T >
struct NoCopyAssignment : BooleanRewrapNegative< _::TypeTraits::HasCopyAssignment<T> > {};

} // namespace TypeTraits

} // namespace BR