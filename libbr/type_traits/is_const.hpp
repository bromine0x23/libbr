/**
 * @file
 * @brief \em const 修饰检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsConst : BooleanFalse {};

template< typename T >
struct IsConst< T const > : BooleanTrue {};

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否包含 \em const 修饰
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotConst
 *
 * 如果 \em T 包含顶层 \em const 修饰，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsConst : BooleanRewrapPositive< Detail::TypeTraits::IsConst<T> > {};

/**
 * @brief IsConst 的否定
 * @tparam T 待检查类型
 * @see IsConst
 */
template< typename T >
struct NotConst : BooleanRewrapNegative< Detail::TypeTraits::IsConst<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsConst 的模板变量版本
 * @tparam T 待检查类型
 * @see IsConst
 * @see not_const
 */
template< typename T >
constexpr auto is_const = bool_constant< IsConst<T> >;

/**
 * @brief NotConst 的模板变量版本
 * @tparam T 待检查类型
 * @see NotConst
 * @see is_const
 */
template< typename T >
constexpr auto not_const = bool_constant< NotConst<T> >;

#endif // defined(BR_CXX14)

} // namespace BR
