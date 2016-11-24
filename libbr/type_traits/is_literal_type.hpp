/**
 * @file
 * @brief \em literal \em type 检查
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_LITERAL_TYPE)
#  include <libbr/type_traits/boolean.hpp>
#  include <libbr/type_traits/is_scalar.hpp>
#  include <libbr/type_traits/is_reference.hpp>
#  include <libbr/type_traits/is_array.hpp>
#  include <libbr/type_traits/remove_const_volatile.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是 \em literal \em type
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see BR_IS_LITERAL_TYPE
 * @see NotLiteralType
 *
 * 如果 \em T 是 \em literal \em type ，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsLiteralType;

/**
 * @brief IsLiteralType 的否定
 * @tparam T 待检查类型
 * @see IsLiteralType
 */
template< typename T >
struct NotLiteralType;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsLiteralType 的模板变量版本
 * @tparam T 待检查类型
 * @see IsLiteralType
 * @see not_literal_type
 */
template< typename T >
constexpr auto is_literal_type = boolean_constant< IsLiteralType<T> >;

/**
 * @brief NotLiteralType 的模板变量版本
 * @tparam T 待检查类型
 * @see NotLiteralType
 * @see is_literal_type
 */
template< typename T >
constexpr auto not_literal_type = boolean_constant< NotLiteralType<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_LITERAL_TYPE)

template< typename T >
using IsLiteralType = BooleanConstant< BR_IS_LITERAL_TYPE(T) >;

#else

template< typename T >
using IsLiteralTypeBasic = BooleanOr< IsScalar<T>, IsReference<T>, IsArrayKnownBounds<T> >;

template< typename T >
using IsLiteralType = IsLiteralTypeBasic< RemoveConstVolatile<T> >;

#endif // defined(BR_IS_LITERAL_TYPE)

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsLiteralType : public BooleanRewrapPositive< Detail::TypeTraits::IsLiteralType<T> > {};

template< typename T >
struct NotLiteralType : public BooleanRewrapNegative< Detail::TypeTraits::IsLiteralType<T> > {};

} // namespace TypeTraits

} // namespace BR