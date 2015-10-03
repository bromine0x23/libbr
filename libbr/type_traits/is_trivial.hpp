/**
 * @file
 * @brief \em trivial 检查
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_TRIVIAL)

template< typename T >
using IsTrivial = BooleanConstant< BR_IS_TRIVIAL(T) >;

#else

template< typename T >
using IsTrivial = BooleanFalse;

#endif // defined(BR_IS_TRIVIAL)

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否是 \em trivial 的
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR_IS_TRIVIAL
 * @see BR::NotTrivial
 *
 * 如果 \em T 是 \em trivial 的，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsTrivial : BooleanRewrapPositive< Detail::TypeTraits::IsTrivial<T> > {};

/**
 * @brief IsTrivial 的否定
 * @tparam T 待检查类型
 * @see BR::IsTrivial
 */
template< typename T >
struct NotTrivial : BooleanRewrapNegative< Detail::TypeTraits::IsTrivial<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsTrivial 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::IsTrivial
 * @see BR::not_trivial
 */
template< typename T >
constexpr auto is_trivial = bool_constant< IsTrivial<T> >;

/**
 * @brief NotTrivial 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NotTrivial
 * @see BR::is_trivial
 */
template< typename T >
constexpr auto not_trivial = bool_constant< NotTrivial<T> >;

#endif // defined(BR_CXX14)

} // namespace BR