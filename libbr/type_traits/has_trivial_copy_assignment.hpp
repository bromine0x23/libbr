/**
 * @file
 * @brief 检查是否具有平凡的(复制)赋值运算符
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_trivially_assignable.hpp>
#include <libbr/type_transform/add_const.hpp>
#include <libbr/type_transform/add_lvalue_reference.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有平凡的(复制)赋值运算符
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsTriviallyAssignable
 * @see HasCopyAssignment
 * @see NoTrivialCopyAssignment
 *
 * 如果 \em T 具有平凡的(复制)赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasTrivialCopyAssignment;

/**
 * @brief HasTrivialCopyAssignment 的否定
 * @tparam T 待检查类型
 * @see HasTrivialCopyAssignment
 */
template< typename T >
struct NoTrivialCopyAssignment;

/**
 * @brief HasTrivialCopyAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see HasTrivialCopyAssignment
 * @see no_trivial_copy_assignment
 */
template< typename T >
constexpr auto has_trivial_copy_assignment  = boolean_constant< HasTrivialCopyAssignment<T> >;

/**
 * @brief NoTrivialCopyAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see NoTrivialCopyAssignment
 * @see has_trivial_copy_assignment
 */
template< typename T >
constexpr auto no_trivial_copy_assignment = boolean_constant< NoTrivialCopyAssignment<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template< typename T >
using HasTrivialCopyAssignment = IsTriviallyAssignable< AddLValueReference<T>, AddLValueReference< AddConst<T> > >;

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct HasTrivialCopyAssignment : BooleanRewrapPositive< _::TypeTraits::HasTrivialCopyAssignment<T> > {};

template< typename T >
struct NoTrivialCopyAssignment : BooleanRewrapNegative< _::TypeTraits::HasTrivialCopyAssignment<T> > {};

} // namespace TypeTraits

} // namespace BR