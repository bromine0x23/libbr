/**
 * @file
 * @brief 检查两个类型是否相同
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T0, typename T1 >
struct IsSame : BooleanFalse {};

template< typename T >
struct IsSame< T, T > : BooleanTrue {};

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T0 、 \em T1 是否相同
 * @tparam T0、T1 待检查类型
 * @see IntegerConstant
 * @see NotSame
 *
 * 如果 \em T0 、 \em T1 是相同，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T0, typename T1 >
struct IsSame : BooleanRewrapPositive< Detail::TypeTraits::IsSame< T0, T1 > > {};

/**
 * @brief IsSame 的否定
 * @tparam T0、T1 待检查类型
 * @see IsSame
 */
template< typename T0, typename T1 >
struct NotSame : BooleanRewrapNegative< Detail::TypeTraits::IsSame< T0, T1 > > {};

#if defined(BR_CXX14)

/**
 * @brief IsSame 的模板变量版本
 * @tparam T0、T1 待检查类型
 * @see IsSame
 * @see not_same
 */
template< typename T0, typename T1 >
constexpr auto is_same = bool_constant< IsSame< T0, T1 > >;

/**
 * @brief NotSame 的模板变量版本
 * @tparam T0、T1 待检查类型
 * @see NotSame
 * @see is_same
 */
template< typename T0, typename T1 >
constexpr auto not_same = bool_constant< NotSame< T0, T1 > >;

#endif // defined(BR_CXX14)

} // namespace BR