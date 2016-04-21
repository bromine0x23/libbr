/**
 * @file
 * @brief \em standard-layout 检查
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_STANDARD_LAYOUT)

template< typename T >
using IsStandardLayout = BooleanConstant< BR_IS_STANDARD_LAYOUT(T) >;

#else

template< typename T >
using IsStandardLayout = BooleanFalse;

#endif // defined(BR_IS_STANDARD_LAYOUT)

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否满足 \em standard-layout 约束
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR_IS_STANDARD_LAYOUT
 * @see BR::NotStandardLayout
 *
 * 如果 \em T 满足 \em standard-layout 约束，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsStandardLayout : BooleanRewrapPositive< Detail::TypeTraits::IsStandardLayout<T> > {};

/**
 * @brief IsStandardLayout 的否定
 * @tparam T 待检查类型
 * @see BR::IsStandardLayout
 */
template< typename T >
struct NotStandardLayout : BooleanRewrapNegative< Detail::TypeTraits::IsStandardLayout<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsStandardLayout 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::IsStandardLayout
 * @see BR::not_standard_layout
 */
template< typename T >
constexpr auto is_standard_layout = bool_constant< IsStandardLayout<T> >;

/**
 * @brief NotStandardLayout 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NotStandardLayout
 * @see BR::is_standard_layout
 */
template< typename T >
constexpr auto not_standard_layout = bool_constant< NotStandardLayout<T> >;

#endif // defined(BR_CXX14)

} // namespace BR