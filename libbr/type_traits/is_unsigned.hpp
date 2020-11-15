/**
 * @file
 * @brief 无符号整型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_arithmetic.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conjunction.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是无符号整型类型
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsSigned
 * @see MakeUnsigned
 * @see NotUnsigned
 *
 * 如果 \em T 是无符号整型类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsUnsigned;

/**
 * @brief IsUnsigned 的否定
 * @tparam T 待检查类型
 * @see IsUnsigned
 */
template< typename T >
struct NotUnsigned;

/**
 * @brief IsUnsigned 的模板变量版本
 * @tparam T 待检查类型
 * @see IsUnsigned
 * @see not_unsigned
 */
template< typename T >
constexpr auto is_unsigned = boolean_constant< IsUnsigned<T> >;

/**
 * @brief NotUnsigned 的模板变量版本
 * @tparam T 待检查类型
 * @see NotUnsigned
 * @see is_unsigned
 */
template< typename T >
constexpr auto not_unsigned = boolean_constant< NotUnsigned<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
struct IsUnsignedBasic : public BooleanConstant< (static_cast<T>(-1) > static_cast<T>(0)) > {};

template< typename T >
struct IsUnsigned : public Conjunction< IsArithmetic<T>, IsUnsignedBasic< RemoveConstVolatile<T> > > {};

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct IsUnsigned : public BooleanRewrapPositive< _::TypeTraits::IsUnsigned<T> > {};

template< typename T >
struct NotUnsigned : public BooleanRewrapNegative< _::TypeTraits::IsUnsigned<T> > {};

} // namespace TypeTraits

} // namespace BR