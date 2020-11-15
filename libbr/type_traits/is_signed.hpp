/**
 * @file
 * @brief 有符号整型检查
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
 * @brief 检查 \em T 是否是有符号整型类型
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see IsUnsigned
 * @see MakeSigned
 * @see NotSigned
 *
 * 如果 \em T 是有符号整型类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsSigned;

/**
 * @brief IsSigned 的否定
 * @tparam T 待检查类型
 * @see IsSigned
 */
template< typename T >
struct NotSigned;

/**
 * @brief IsSigned 的模板变量版本
 * @tparam T 待检查类型
 * @see IsSigned
 * @see not_signed
 */
template< typename T >
constexpr auto is_signed = boolean_constant< IsSigned<T> >;

/**
 * @brief NotSigned 的模板变量版本
 * @tparam T 待检查类型
 * @see NotSigned
 * @see is_signed
 */
template< typename T >
constexpr auto not_signed = boolean_constant< NotSigned<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
struct IsSignedBasic : public BooleanConstant< (static_cast<T>(-1) < static_cast<T>(0)) > {};

template< typename T >
struct IsSigned : public Conjunction< IsArithmetic<T>, IsSignedBasic< RemoveConstVolatile<T> > > {};

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct IsSigned : public BooleanRewrapPositive< _::TypeTraits::IsSigned<T> > {};

template< typename T >
struct NotSigned : public BooleanRewrapNegative< _::TypeTraits::IsSigned<T> > {};

} // namespace TypeTraits

} // namespace BR