/**
 * @file
 * @brief 检查是否具有移动赋值运算符
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_traits/is_assignable.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using HasMoveAssign = IsAssignable< AddLValueReference<T>, AddRValueReference<T> >;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否重载了移动赋值运算符
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsAssignable
 * @see BR::NoMoveAssign
 *
 * 如果 \em T 重载了移动赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasMoveAssign : BooleanRewrapPositive< Detail::TypeTraits::HasMoveAssign<T> > {};

/**
 * @brief HasMoveAssign 的否定
 * @tparam T 待检查类型
 * @see BR::HasMoveAssign
 */
template< typename T >
struct NoMoveAssign: BooleanRewrapNegative< Detail::TypeTraits::HasMoveAssign<T> > {};

#if defined(BR_CXX14)

/**
 * @brief HasMoveAssign 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasMoveAssign
 * @see BR::no_move_assign
 */
template< typename T >
constexpr auto has_move_assign = bool_constant< HasMoveAssign<T> >;

/**
 * @brief NoMoveAssign 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoMoveAssign
 * @see BR::no_move_assign
 */
template< typename T >
constexpr auto no_move_assign = bool_constant< NoMoveAssign<T> >;

#endif // defined(BR_CXX14)

} // namespace BR