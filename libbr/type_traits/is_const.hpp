/**
 * @file
 * @brief \em const 修饰检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否包含 \em const 修饰
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotConst
 *
 * 如果 \em T 包含顶层 \em const 修饰，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsConst;

/**
 * @brief IsConst 的否定
 * @tparam T 待检查类型
 * @see IsConst
 */
template< typename T >
struct NotConst;

/**
 * @brief IsConst 的模板变量版本
 * @tparam T 待检查类型
 * @see IsConst
 * @see not_const
 */
template< typename T >
constexpr auto is_const = boolean_constant< IsConst<T> >;

/**
 * @brief NotConst 的模板变量版本
 * @tparam T 待检查类型
 * @see NotConst
 * @see is_const
 */
template< typename T >
constexpr auto not_const = boolean_constant< NotConst<T> >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template< typename T >
struct IsConst : public BooleanFalse {};

template< typename T >
struct IsConst< T const > : public BooleanTrue {};

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct IsConst : public BooleanRewrapPositive< _::TypeTraits::IsConst<T> > {};

template< typename T >
struct NotConst : public BooleanRewrapNegative< _::TypeTraits::IsConst<T> > {};

} // namespace TypeTraits

} // namespace BR
