/**
 * @file
 * @brief \em literal \em type 检查
 * @author Bromine0x23
 * @since 2015/10/3
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_LITERAL_TYPE)
#  include <libbr/type_operate/bool.hpp>
#  include <libbr/type_operate/remove_const_volatile.hpp>
#  include <libbr/type_traits/is_scalar.hpp>
#  include <libbr/type_traits/is_reference.hpp>
#  include <libbr/type_traits/is_array.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_LITERAL_TYPE)

template< typename T >
using IsLiteralType = BooleanConstant< BR_IS_LITERAL_TYPE(T) >;

#else

template< typename T >
using IsLiteralTypeBasic = BooleanOr<
	IsScalar<T>,
	IsReference<T>,
	IsArrayKnownBounds<T>
>;

template< typename T >
using IsLiteralType = IsLiteralTypeBasic< RemoveConstVolatile<T> >;

#endif // defined(BR_IS_LITERAL_TYPE)

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否是 \em literal \em type
 * @tparam T 待检查类型
 * @see BR::IntegerConstant
 * @see BR_IS_LITERAL_TYPE
 * @see BR::NotLiteralType
 *
 * 如果 \em T 是 \em literal \em type ，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsLiteralType : BooleanRewrapPositive< Detail::TypeTraits::IsLiteralType<T> > {};

/**
 * @brief IsLiteralType 的否定
 * @tparam T 待检查类型
 * @see BR::IsLiteralType
 */
template< typename T >
struct NotLiteralType : BooleanRewrapNegative< Detail::TypeTraits::IsLiteralType<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsLiteralType 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::IsLiteralType
 * @see BR::not_literal_type
 */
template< typename T >
constexpr auto is_literal_type = bool_constant< IsLiteralType<T> >;

/**
 * @brief NotLiteralType 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::NotLiteralType
 * @see BR::is_literal_type
 */
template< typename T >
constexpr auto not_literal_type = bool_constant< NotLiteralType<T> >;

#endif // defined(BR_CXX14)

} // namespace BR