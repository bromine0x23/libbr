/**
 * @file
 * @brief 检查是否具有平凡的移动赋值运算符
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_traits/is_trivially_assignable.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using HasTrivialMoveAssign = IsTriviallyAssignable < AddLValueReference<T>, AddRValueReference<T> >;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否具有平凡的移动赋值运算符
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsTriviallyAssignable
 * @see BR::HasMoveAssign
 * @see BR::NoTrivialMoveAssign
 *
 * 如果 \em T 具有平凡的移动赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasTrivialMoveAssign : BooleanRewrapPositive< Detail::TypeTraits::HasTrivialMoveAssign<T> > {};

/**
 * @brief HasTrivialMoveAssign 的否定
 * @tparam T 待检查类型
 * @see BR::HasTrivialMoveAssign
 */
template< typename T >
struct NoTrivialMoveAssign : BooleanRewrapNegative< Detail::TypeTraits::HasTrivialMoveAssign<T> > {};

#if defined(BR_CXX14)

/**
 * @brief HasTrivialMoveAssign 的模板变量版本
 * @tparam T 待检查类型
 * @see HasTrivialMoveAssign
 * @see no_trivial_move_assign
 */
template< typename T >
constexpr auto has_trivial_move_assign = bool_constant< HasTrivialMoveAssign<T> >;

/**
 * @brief NoTrivialMoveAssign 的模板变量版本
 * @tparam T 待检查类型
 * @see NoTrivialMoveAssign
 * @see has_trivial_move_assign
 */
template< typename T >
constexpr auto no_trivial_move_assign = bool_constant< NoTrivialMoveAssign<T> >;

#endif // defined(BR_CXX14)

} // namespace BR