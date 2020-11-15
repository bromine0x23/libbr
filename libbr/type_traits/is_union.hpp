/**
 * @file
 * @brief 联合类型检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是联合类型
 * @tparam T 待检查类型
 * @see Utility::IntegralConstant
 * @see BR_IS_UNION
 * @see NotUnion
 *
 * 如果 \em T 是联合类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsUnion;

/**
 * @brief IsUnion 的否定
 * @tparam T 待检查类型
 * @see IsUnion
 */
template< typename T >
struct NotUnion;

/**
 * @brief IsUnion 的模板变量版本
 * @tparam T 待检查类型
 * @see IsUnion
 * @see not_union
 */
template< typename T >
constexpr auto is_union = boolean_constant< IsUnion<T> >;

/**
 * @brief NotUnion 的模板变量版本
 * @tparam T 待检查类型
 * @see NotUnion
 * @see is_union
 */
template< typename T >
constexpr auto not_union = boolean_constant< NotUnion<T> >;

} // namespace TypeTraits



namespace _::TypeTraits {

#if defined(BR_IS_UNION)

template< typename T >
using IsUnion = BooleanConstant< BR_IS_UNION(T) >;

#else

template< typename T >
using IsUnion = BooleanFalse;

#endif // defined(BR_IS_UNION)

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct IsUnion : public BooleanRewrapPositive< _::TypeTraits::IsUnion<T> > {};

template< typename T >
struct NotUnion : public BooleanRewrapNegative< _::TypeTraits::IsUnion<T> > {};

} // namespace TypeTraits

} // namespace BR

