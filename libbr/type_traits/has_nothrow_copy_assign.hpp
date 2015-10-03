/**
 * @file
 * @brief 检查是否具有 \em nothrow 的(复制)赋值运算符
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_traits/is_nothrow_assignable.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using HasNothrowCopyAssign = IsNothrowAssignable< AddLValueReference<T>, AddLValueReference< AddConst<T> > >;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否可被 \em nothrow 地拷贝赋值
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsNothrowAssignable
 * @see BR::HasCopyAssign
 * @see BR::NoNothrowCopyAssign
 *
 * 如果 \em T 可被 \em nothrow 地拷贝赋值，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasNothrowCopyAssign : BooleanRewrapPositive< Detail::TypeTraits::HasNothrowCopyAssign<T> > {};

/**
 * @brief HasNothrowCopyAssign 的否定
 * @tparam T 待检查类型
 * @see BR::HasNothrowCopyAssign
 */
template< typename T >
struct NoNothrowCopyAssign : BooleanRewrapNegative< Detail::TypeTraits::HasNothrowCopyAssign<T> > {};

#if defined(BR_CXX14)

/**
 * @brief HasNothrowCopyAssign 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasNothrowCopyAssign
 * @see BR::no_nothrow_copy_assign
 */
template< typename T >
constexpr auto has_nothrow_copy_assign = bool_constant< HasNothrowCopyAssign<T> >;

/**
 * @brief NoNothrowCopyAssign 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoNothrowCopyAssign
 * @see BR::has_nothrow_copy_assign
 */
template< typename T >
constexpr auto no_nothrow_copy_assign = bool_constant< NoNothrowCopyAssign<T> >;

#endif // defined(BR_CXX14)

} // namespace BR