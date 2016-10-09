/**
 * @file
 * @brief 标量类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/is_arithmetic.hpp>
#include <libbr/type_traits/is_enum.hpp>
#include <libbr/type_traits/is_member_pointer.hpp>
#include <libbr/type_traits/is_null_pointer.hpp>
#include <libbr/type_traits/is_pointer.hpp>

namespace BR {

/**
 * @brief 检查 \em T 是否是指针类型
 * @tparam T 待检查类型
 * @see IntegerConstant
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

#if defined(BR_CXX14)

/**
 * @brief IsScalar 的模板变量版本
 * @tparam T 待检查类型
 * @see IsScalar
 * @see not_scalar
 */
template< typename T >
constexpr auto is_scalar = bool_constant< IsScalar<T> >;

/**
 * @brief NotScalar 的模板变量版本
 * @tparam T 待检查类型
 * @see NotScalar
 * @see is_scalar
 */
template< typename T >
constexpr auto not_scalar = bool_constant< NotScalar<T> >;

#endif // defined(BR_CXX14)

namespace Detail {
namespace TypeTraits {

template< typename T >
using IsScalar = BooleanOr< IsArithmetic<T>, IsEnum<T>, IsPointer<T>, IsNullPointer<T>, IsMemberPointer<T> >;

} // namespace TypeTraits
} // namespace Detail

template< typename T >
struct IsScalar : public BooleanRewrapPositive< Detail::TypeTraits::IsScalar<T> > {};

template< typename T >
struct NotScalar : public BooleanRewrapNegative< Detail::TypeTraits::IsScalar<T> > {};

} // namespace BR