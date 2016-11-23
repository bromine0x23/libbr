/**
 * @file
 * @brief 检查是否具有移动赋值运算符
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/add_lvalue_reference.hpp>
#include <libbr/type_traits/add_rvalue_reference.hpp>
#include <libbr/type_traits/is_assignable.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否重载了移动赋值运算符
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsAssignable
 * @see NoMoveAssignment
 *
 * 如果 \em T 重载了移动赋值运算符，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct HasMoveAssignment;

/**
 * @brief HasMoveAssignment 的否定
 * @tparam T 待检查类型
 * @see HasMoveAssignment
 */
template< typename T >
struct NoMoveAssignment;

#if defined(BR_AFTER_CXX11)

/**
 * @brief HasMoveAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see HasMoveAssignment
 * @see no_move_assignment
 */
template< typename T >
constexpr auto has_move_assignment = boolean_constant< HasMoveAssignment<T> >;

/**
 * @brief NoMoveAssignment 的模板变量版本
 * @tparam T 待检查类型
 * @see NoMoveAssignment
 * @see has_move_assignment
 */
template< typename T >
constexpr auto no_move_assignment = boolean_constant< NoMoveAssignment<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
using HasMoveAssignment = IsAssignable< AddLValueReference<T>, AddRValueReference<T> >;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct HasMoveAssignment : public BooleanRewrapPositive< Detail::TypeTraits::HasMoveAssignment<T> > {};

template< typename T >
struct NoMoveAssignment : public BooleanRewrapNegative< Detail::TypeTraits::HasMoveAssignment<T> > {};

} // namespace TypeTraits

} // namespace BR