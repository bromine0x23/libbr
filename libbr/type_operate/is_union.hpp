/**
 * @file
 * @brief 联合类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_UNION)

template< typename T >
using IsUnion = BooleanConstant< BR_IS_UNION(T) >;

#else

template< typename T >
using IsUnion = BooleanFalse;

#endif // defined(BR_IS_UNION)

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否是联合类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotUnion
 *
 * 如果 \em T 是联合类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsUnion : Boolean< Detail::TypeOperate::IsUnion<T> > {};

/**
 * @brief IsUnion 的否定
 * @tparam T 待检查类型
 * @see IsUnion
 */
template< typename T >
struct NotUnion : BooleanNot< Detail::TypeOperate::IsUnion<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsUnion 的模板变量版本
 * @tparam T 待检查类型
 * @see IsUnion
 * @see not_union
 */
template< typename T >
constexpr auto is_union = IsUnion<T>::value;

/**
 * @brief NotUnion 的模板变量版本
 * @tparam T 待检查类型
 * @see NotUnion
 * @see is_union
 */
template< typename T >
constexpr auto not_union = NotUnion<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR

