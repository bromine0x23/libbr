/**
 * @file
 * @brief \em trivial 检查
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是 \em trivial 的
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see BR_IS_TRIVIAL
 * @see NotTrivial
 *
 * 如果 \em T 是 \em trivial 的，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsTrivial;

/**
 * @brief IsTrivial 的否定
 * @tparam T 待检查类型
 * @see IsTrivial
 */
template< typename T >
struct NotTrivial;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsTrivial 的模板变量版本
 * @tparam T 待检查类型
 * @see IsTrivial
 * @see not_trivial
 */
template< typename T >
constexpr auto is_trivial = boolean_constant< IsTrivial<T> >;

/**
 * @brief NotTrivial 的模板变量版本
 * @tparam T 待检查类型
 * @see NotTrivial
 * @see is_trivial
 */
template< typename T >
constexpr auto not_trivial = boolean_constant< NotTrivial<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



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

inline namespace TypeTraits {

template< typename T >
struct IsTrivial : public BooleanRewrapPositive< Detail::TypeTraits::IsTrivial<T> > {};

template< typename T >
struct NotTrivial : public BooleanRewrapNegative< Detail::TypeTraits::IsTrivial<T> > {};

} // namespace TypeTraits

} // namespace BR