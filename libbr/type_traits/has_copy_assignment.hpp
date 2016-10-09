/**
 * @file
 * @brief 检查是否具有(复制)赋值运算符
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_traits/is_assignable.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否具有(复制)赋值运算符
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR::IsAssignable
 * @see BR::NoCopyAssignment
 *
 * 如果 \em T 具有(复制)赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasCopyAssignment;

/**
 * @brief HasCopyAssignment 的否定
 * @tparam T 待检查类型
 * @see BR::HasCopyAssignment
 */
template< typename T >
struct NoCopyAssignment;

#if defined(BR_CXX14)

/**
 * @brief HasCopyAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::HasCopyAssignment
 * @see BR::no_copy_assignment
 */
template< typename T >
constexpr auto has_copy_assignment = bool_constant< HasCopyAssignment<T> >;

/**
 * @brief NoCopyAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NoCopyAssignment
 * @see BR::has_copy_assignment
 */
template< typename T >
constexpr auto no_copy_assignment = bool_constant< NoCopyAssignment<T> >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

template< typename T >
using HasCopyAssignment = IsAssignable< AddLValueReference<T>, AddLValueReference< AddConst<T> > >;

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct HasCopyAssignment : BooleanRewrapPositive< Detail::TypeTraits::HasCopyAssignment<T> > {};

template< typename T >
struct NoCopyAssignment : BooleanRewrapNegative< Detail::TypeTraits::HasCopyAssignment<T> > {};

} // namespace BR