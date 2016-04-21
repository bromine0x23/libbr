/**
 * @file
 * @brief 检查是否具有 \em nothrow 的移动赋值运算符
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_traits/is_nothrow_assignable.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using HasNothrowMoveAssign = IsNothrowAssignable< AddLValueReference<T>, AddRValueReference<T> >;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否具有 \em nothrow 的移动赋值运算符
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsNothrowAssignable
 * @see BR::HasMoveAssign
 * @see BR::NoNothrowMoveAssign
 *
 * 如果 \em T 具有 \em nothrow 的移动赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasNothrowMoveAssign : BooleanRewrapPositive< Detail::TypeTraits::HasNothrowMoveAssign<T> > {};

/**
 * @brief HasNothrowMoveAssign 的否定
 * @tparam T 待检查类型
 * @see BR::HasNothrowMoveAssign
 */
template< typename T >
struct NoNothrowMoveAssign : BooleanRewrapNegative< Detail::TypeTraits::HasNothrowMoveAssign<T> > {};

#if defined(BR_CXX14)

/**
 * @brief HasNothrowMoveAssign 的模板变量版本
 * @tparam T 待检查类型
 * @see HasNothrowMoveAssign
 * @see no_nothrow_move_assign
 */
template< typename T >
constexpr auto has_nothrow_move_assign = bool_constant< HasNothrowMoveAssign<T> >;

/**
 * @brief NoNothrowMoveAssign 的模板变量版本
 * @tparam T 待检查类型
 * @see NoNothrowMoveAssign
 * @see has_nothrow_move_assign
 */
template< typename T >
constexpr auto no_nothrow_move_assign = bool_constant< NoNothrowMoveAssign<T> >;

#endif // defined(BR_CXX14)

} // namespace BR