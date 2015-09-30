/**
 * @file
 * @brief 浮点类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

using BR::RemoveConstVolatile;

template< typename T >
struct IsFloatingPointBasic : BooleanFalse {};

template<>
struct IsFloatingPointBasic<float> : BooleanTrue {};

template<>
struct IsFloatingPointBasic<double> : BooleanTrue {};

template<>
struct IsFloatingPointBasic<long double> : BooleanTrue {};

template< typename T >
using IsFloatingPoint = IsFloatingPointBasic< RemoveConstVolatile<T> >;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是浮点类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotFloatingPoint
 *
 * 如果\em T 是浮点类型(\em float、\em double、\em long \em double 及其带CV修饰的版本)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsFloatingPoint : Boolean< Detail::TypeOperate::IsFloatingPoint<T> > {};

/**
 * @brief IsFloatingPoint 的否定
 * @tparam T 待检查类型
 * @see IsFloatingPoint
 */
template< typename T >
struct NotFloatingPoint : BooleanNot< Detail::TypeOperate::IsFloatingPoint<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsFloatingPoint 的模板变量版本
 * @tparam T 待检查类型
 * @see IsFloatingPoint
 * @see not_floating_point
 */
template< typename T >
constexpr auto is_floating_point = IsFloatingPoint<T>::value;

/**
 * @brief NotFloatingPoint 的模板变量版本
 * @tparam T 待检查类型
 * @see NotFloatingPoint
 * @see is_floating_point
 */
template< typename T >
constexpr auto not_floating_point = NotFloatingPoint<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR