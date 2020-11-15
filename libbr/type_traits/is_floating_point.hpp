/**
 * @file
 * @brief 浮点类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是浮点类型
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see NotFloatingPoint
 *
 * 如果\em T 是浮点类型(\em float、\em double、\em long \em double 及其带CV修饰的版本)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsFloatingPoint;

/**
 * @brief IsFloatingPoint 的否定
 * @tparam T 待检查类型
 * @see IsFloatingPoint
 */
template< typename T >
struct NotFloatingPoint;

/**
 * @brief IsFloatingPoint 的模板变量版本
 * @tparam T 待检查类型
 * @see IsFloatingPoint
 * @see not_floating_point
 */
template< typename T >
constexpr auto is_floating_point = boolean_constant< IsFloatingPoint<T> >;

/**
 * @brief NotFloatingPoint 的模板变量版本
 * @tparam T 待检查类型
 * @see NotFloatingPoint
 * @see is_floating_point
 */
template< typename T >
constexpr auto not_floating_point = boolean_constant< NotFloatingPoint<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

template< typename T >
struct IsFloatingPointBasic : public BooleanFalse {};

template<> struct IsFloatingPointBasic<float>       : public BooleanTrue {};
template<> struct IsFloatingPointBasic<double>      : public BooleanTrue {};
template<> struct IsFloatingPointBasic<long double> : public BooleanTrue {};

template< typename T >
using IsFloatingPoint = IsFloatingPointBasic< RemoveConstVolatile<T> >;

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct IsFloatingPoint : public BooleanRewrapPositive< _::TypeTraits::IsFloatingPoint<T> > {};

template< typename T >
struct NotFloatingPoint : public BooleanRewrapNegative< _::TypeTraits::IsFloatingPoint<T> > {};

} // namespace TypeTraits

} // namespace BR