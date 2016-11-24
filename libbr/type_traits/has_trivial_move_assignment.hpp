/**
 * @file
 * @brief 检查是否具有平凡的移动赋值运算符
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/add_lvalue_reference.hpp>
#include <libbr/type_traits/add_rvalue_reference.hpp>
#include <libbr/type_traits/is_trivially_assignable.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否具有平凡的移动赋值运算符
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsTriviallyAssignable
 * @see HasMoveAssignment
 * @see NoTrivialMoveAssignment
 *
 * 如果 \em T 具有平凡的移动赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasTrivialMoveAssignment;

/**
 * @brief HasTrivialMoveAssignment 的否定
 * @tparam T 待检查类型
 * @see HasTrivialMoveAssignment
 */
template< typename T >
struct NoTrivialMoveAssignment;

#if defined(BR_AFTER_CXX11)

/**
 * @brief HasTrivialMoveAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see HasTrivialMoveAssignment
 * @see no_trivial_move_assignment
 */
template< typename T >
constexpr auto has_trivial_move_assignment = boolean_constant< HasTrivialMoveAssignment<T> >;

/**
 * @brief NoTrivialMoveAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see NoTrivialMoveAssignment
 * @see has_trivial_move_assignment
 */
template< typename T >
constexpr auto no_trivial_move_assignment = boolean_constant< NoTrivialMoveAssignment<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
using HasTrivialMoveAssignment = IsTriviallyAssignable < AddLValueReference<T>, AddRValueReference<T> >;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct HasTrivialMoveAssignment : public BooleanRewrapPositive< Detail::TypeTraits::HasTrivialMoveAssignment<T> > {};

template< typename T >
struct NoTrivialMoveAssignment : public BooleanRewrapNegative< Detail::TypeTraits::HasTrivialMoveAssignment<T> > {};

} // namespace TypeTraits

} // namespace BR