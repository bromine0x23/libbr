/**
 * @file
 * @brief \em standard-layout 检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#include <libbr/utility/boolean_constant.hpp>
#if !defined(BR_IS_STANDARD_LAYOUT)
#  include <libbr/type_traits/is_scalar.hpp>
#  include <libbr/type_transform/remove_all_extents.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否满足 \em standard-layout 约束
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see BR_IS_STANDARD_LAYOUT
 * @see NotStandardLayout
 *
 * 如果 \em T 满足 \em standard-layout 约束，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsStandardLayout;

/**
 * @brief IsStandardLayout 的否定
 * @tparam T 待检查类型
 * @see IsStandardLayout
 */
template< typename T >
struct NotStandardLayout;

/**
 * @brief IsStandardLayout 的模板变量版本
 * @tparam T 待检查类型
 * @see IsStandardLayout
 * @see not_standard_layout
 */
template< typename T >
constexpr auto is_standard_layout = boolean_constant< IsStandardLayout<T> >;

/**
 * @brief NotStandardLayout 的模板变量版本
 * @tparam T 待检查类型
 * @see NotStandardLayout
 * @see is_standard_layout
 */
template< typename T >
constexpr auto not_standard_layout = boolean_constant< NotStandardLayout<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

#if defined(BR_IS_STANDARD_LAYOUT)

template< typename T >
using IsStandardLayout = BooleanConstant< BR_IS_STANDARD_LAYOUT(T) >;

#else

template< typename T >
using IsStandardLayout = IsScalar< RemoveAllExtents<T> >;

#endif // defined(BR_IS_STANDARD_LAYOUT)

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct IsStandardLayout : public BooleanRewrapPositive< _::TypeTraits::IsStandardLayout<T> > {};

template< typename T >
struct NotStandardLayout : public BooleanRewrapNegative< _::TypeTraits::IsStandardLayout<T> > {};

} // namespace TypeTraits

} // namespace BR