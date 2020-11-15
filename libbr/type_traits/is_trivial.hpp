/**
 * @file
 * @brief \em trivial 检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#include <libbr/utility/boolean_constant.hpp>
#if !defined(BR_IS_TRIVIAL)
#  include <libbr/type_traits/has_trivial_copy_constructor.hpp>
#  include <libbr/type_traits/has_trivial_default_constructor.hpp>
#  include <libbr/utility/conjunction.hpp>
#endif

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

} // namespace TypeTraits



namespace _::TypeTraits {

#if defined(BR_IS_TRIVIAL)

template< typename T >
using IsTrivial = BooleanConstant< BR_IS_TRIVIAL(T) >;

#else

template< typename T >
using IsTrivial = Conjunction< HasTrivialCopyConstructor<T>, HasTrivialDefaultConstructor<T> >;

#endif // defined(BR_IS_TRIVIAL)

} // namespace _::TypeTraits

inline namespace TypeTraits {

template< typename T >
struct IsTrivial : public BooleanRewrapPositive< _::TypeTraits::IsTrivial<T> > {};

template< typename T >
struct NotTrivial : public BooleanRewrapNegative< _::TypeTraits::IsTrivial<T> > {};

} // namespace TypeTraits

} // namespace BR