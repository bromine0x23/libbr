/**
 * @file
 * @brief 检查是否具有(复制)赋值运算符
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_traits/is_assignable.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
using HasCopyAssign = IsAssignable< AddLValueReference<T>, AddLValueReference< AddConst<T> > >;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否具有(复制)赋值运算符
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsAssignable
 * @see BR::NoCopyAssign
 *
 * 如果 \em T 具有(复制)赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasCopyAssign : BooleanRewrapPositive< Detail::TypeTraits::HasCopyAssign<T> > {};

/**
 * @brief HasCopyAssign 的否定
 * @tparam T 待检查类型
 * @see BR::HasCopyAssign
 */
template< typename T >
struct NoCopyAssign : BooleanRewrapNegative< Detail::TypeTraits::HasCopyAssign<T> > {};

#if defined(BR_CXX14)

/**
 * @brief HasCopyAssign 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasCopyAssign
 * @see BR::no_copy_assign
 */
template< typename T >
constexpr auto has_copy_assign = bool_constant< HasCopyAssign<T> >;

/**
 * @brief NoCopyAssign 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoCopyAssign
 * @see BR::has_copy_assign
 */
template< typename T >
constexpr auto no_copy_assign = bool_constant< NoCopyAssign<T> >;

#endif // defined(BR_CXX14)

} // namespace BR