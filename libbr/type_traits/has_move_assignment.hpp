/**
 * @file
 * @brief 检查是否具有移动赋值运算符
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_transform/add_lvalue_reference.hpp>
#include <libbr/type_transform/add_rvalue_reference.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否重载了移动赋值运算符
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsAssignable
 * @see NoMoveAssignment
 *
 * 如果 \em T 重载了移动赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasMoveAssignment;

/**
 * @brief HasMoveAssignment 的否定
 * @tparam T 待检查类型
 * @see HasMoveAssignment
 */
template< typename T >
struct NoMoveAssignment;

/**
 * @brief HasMoveAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see HasMoveAssignment
 * @see no_move_assignment
 */
template< typename T >
constexpr auto has_move_assignment = boolean_constant< HasMoveAssignment<T> >;

/**
 * @brief NoMoveAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see NoMoveAssignment
 * @see has_move_assignment
 */
template< typename T >
constexpr auto no_move_assignment = boolean_constant< NoMoveAssignment<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
using HasMoveAssignment = IsAssignable< AddLValueReference<T>, AddRValueReference<T> >;

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct HasMoveAssignment : public BooleanRewrapPositive< _::TypeTraits::HasMoveAssignment<T> > {};

template< typename T >
struct NoMoveAssignment : public BooleanRewrapNegative< _::TypeTraits::HasMoveAssignment<T> > {};

} // namespace TypeTraits

} // namespace BR