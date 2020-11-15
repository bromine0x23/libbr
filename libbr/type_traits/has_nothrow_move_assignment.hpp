/**
 * @file
 * @brief 检查是否具有 \em nothrow 的移动赋值运算符
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_nothrow_assignable.hpp>
#include <libbr/type_transform/add_lvalue_reference.hpp>
#include <libbr/type_transform/add_rvalue_reference.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有 \em nothrow 的移动赋值运算符
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsNothrowAssignable
 * @see HasMoveAssignment
 * @see NoNothrowMoveAssignment
 *
 * 如果 \em T 具有 \em nothrow 的移动赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasNothrowMoveAssignment;

/**
 * @brief HasNothrowMoveAssignment 的否定
 * @tparam T 待检查类型
 * @see HasNothrowMoveAssignment
 */
template< typename T >
struct NoNothrowMoveAssignment;

/**
 * @brief HasNothrowMoveAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see HasNothrowMoveAssignment
 * @see no_nothrow_move_assignment
 */
template< typename T >
constexpr auto has_nothrow_move_assignment = boolean_constant< HasNothrowMoveAssignment<T> >;

/**
 * @brief NoNothrowMoveAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see NoNothrowMoveAssignment
 * @see has_nothrow_move_assignment
 */
template< typename T >
constexpr auto no_nothrow_move_assignment = boolean_constant< NoNothrowMoveAssignment<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
using HasNothrowMoveAssignment = IsNothrowAssignable< AddLValueReference<T>, AddRValueReference<T> >;

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct HasNothrowMoveAssignment : public BooleanRewrapPositive< _::TypeTraits::HasNothrowMoveAssignment<T> > {};

template< typename T >
struct NoNothrowMoveAssignment : public BooleanRewrapNegative< _::TypeTraits::HasNothrowMoveAssignment<T> > {};

} // namespace TypeTraits

} // namespace BR