/**
 * @file
 * @brief 标量类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_arithmetic.hpp>
#include <libbr/type_traits/is_enum.hpp>
#include <libbr/type_traits/is_member_pointer.hpp>
#include <libbr/type_traits/is_null_pointer.hpp>
#include <libbr/type_traits/is_pointer.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/disjunction.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是指针类型
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsArithmetic
 * @see IsEnum
 * @see IsPointer
 * @see IsNullPointer
 * @see IsMemberPointer
 * @see NotScalar
 *
 * 如果 \em T 是标量类型(算术类型、枚举类型、指针、成员指针、空指针及其带CV修饰的版本)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsScalar;

/**
 * @brief IsScalar 的否定
 * @tparam T 待检查类型
 * @see IsScalar
 */
template< typename T >
struct NotScalar;

/**
 * @brief IsScalar 的模板变量版本
 * @tparam T 待检查类型
 * @see IsScalar
 * @see not_scalar
 */
template< typename T >
constexpr auto is_scalar = boolean_constant< IsScalar<T> >;

/**
 * @brief NotScalar 的模板变量版本
 * @tparam T 待检查类型
 * @see NotScalar
 * @see is_scalar
 */
template< typename T >
constexpr auto not_scalar = boolean_constant< NotScalar<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
using IsScalar = Disjunction< IsArithmetic<T>, IsEnum<T>, IsPointer<T>, IsNullPointer<T>, IsMemberPointer<T> >;

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct IsScalar : public BooleanRewrapPositive< _::TypeTraits::IsScalar<T> > {};

template< typename T >
struct NotScalar : public BooleanRewrapNegative< _::TypeTraits::IsScalar<T> > {};

} // namespace TypeTraits

} // namespace BR