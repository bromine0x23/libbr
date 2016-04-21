/**
 * @file
 * @brief \em final 类类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_FINAL)

template< typename T >
using IsFinal = BooleanConstant< BR_IS_FINAL(T) >;

#else

template< typename T >
using IsFinal = BooleanFalse;

#endif // BR_IS_FINAL

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否是 \em final 类
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotFinal
 *
 * 如果 \em T 是带\em final 修饰的类类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsFinal : BooleanRewrapPositive< Detail::TypeTraits::IsFinal<T> > {};

/**
 * @brief IsFinal 的否定
 * @tparam T 待检查类型
 * @see IsFinal
 */
template< typename T >
struct NotFinal : BooleanRewrapNegative< Detail::TypeTraits::IsFinal<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsFinal 的模板变量版本
 * @tparam T 待检查类型
 * @see IsFinal
 * @see not_final
 */
template< typename T >
constexpr auto is_final = bool_constant< IsFinal<T> >;

/**
 * @brief NotFinal 的模板变量版本
 * @tparam T 待检查类型
 * @see NotFinal
 * @see is_final
 */
template< typename T >
constexpr auto not_final = bool_constant< NotFinal<T> >;

#endif // defined(BR_CXX14)

} // namespace BR