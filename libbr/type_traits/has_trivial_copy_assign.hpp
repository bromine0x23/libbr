/**
 * @file
 * @brief 检查是否具有平凡的(复制)赋值运算符
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_traits/is_trivially_assignable.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using HasTrivialCopyAssign = IsTriviallyAssignable< AddLValueReference<T>, AddLValueReference< AddConst<T> > >;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否具有平凡的(复制)赋值运算符
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsTriviallyAssignable
 * @see BR::HasCopyAssign
 * @see BR::NoTrivialCopyAssign
 *
 * 如果 \em T 具有平凡的(复制)赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasTrivialCopyAssign : BooleanRewrapPositive< Detail::TypeTraits::HasTrivialCopyAssign<T> > {};

/**
 * @brief HasTrivialCopyAssign 的否定
 * @tparam T 待检查类型
 * @see BR::HasTrivialCopyAssign
 */
template< typename T >
struct NoTrivialCopyAssign : BooleanRewrapNegative< Detail::TypeTraits::HasTrivialCopyAssign<T> > {};

#if defined(BR_CXX14)

/**
 * @brief HasTrivialCopyAssign 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasTrivialCopyAssign
 * @see BR::no_trivial_copy_assign
 */
template< typename T >
constexpr auto has_trivial_copy_assign = bool_constant< HasTrivialCopyAssign<T> >;

/**
 * @brief NoTrivialCopyAssign 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoTrivialCopyAssign
 * @see BR::has_trivial_copy_assign
 */
template< typename T >
constexpr auto no_trivial_copy_assign = bool_constant< NoTrivialCopyAssign<T> >;

#endif // defined(BR_CXX14)

} // namespace BR