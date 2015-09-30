/**
 * @file
 * @brief 基本类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_arithmetic.hpp>
#include <libbr/type_operate/is_void.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsFundamental = BooleanOr< IsArithmetic<T>, IsVoid<T> >;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是基本类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsArithmetic
 * @see IsVoid
 * @see NotCompound
 *
 * 如果 \em T 是基本类型(算术类型或 \em void)，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsFundamental : Boolean< Detail::TypeOperate::IsFundamental<T> > {};

/**
 * @brief IsFundamental 的否定
 * @tparam T 待检查类型
 * @see IsFundamental
 */
template< typename T >
struct NotFundamental : BooleanNot< Detail::TypeOperate::IsFundamental<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsFundamental 的模板变量版本
 * @tparam T 待检查类型
 * @see IsFundamental
 * @see not_fundamental
 */
template< typename T >
constexpr auto is_fundamental = IsFundamental<T>::value;

/**
 * @brief NotFundamental 的模板变量版本
 * @tparam T 待检查类型
 * @see NotFundamental
 * @see is_fundamental
 */
template< typename T >
constexpr auto not_fundamental = NotFundamental<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR

