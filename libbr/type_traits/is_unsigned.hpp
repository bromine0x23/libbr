/**
 * @file
 * @brief 无符号整型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_traits/is_integer.hpp>
#include <libbr/type_traits/is_enum.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsUnsignedBasic {
	using Type = RemoveConstVolatile<T>;
	constexpr static auto value = static_cast<Type>(-1) > static_cast<Type>(0);
};

template< typename T >
using IsUnsigned = BooleanAnd< BooleanOr< IsInteger<T>, IsEnum<T> >, BooleanConstant< IsUnsignedBasic<T>::value > >;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否是无符号整型类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsSigned
 * @see MakeUnsigned
 * @see NotUnsigned
 *
 * 如果 \em T 是无符号整型类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsUnsigned : BooleanRewrapPositive< Detail::TypeTraits::IsUnsigned<T> > {};

/**
 * @brief IsUnsigned 的否定
 * @tparam T 待检查类型
 * @see IsUnsigned
 */
template< typename T >
struct NotUnsigned : BooleanRewrapNegative< Detail::TypeTraits::IsUnsigned<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsUnsigned 的模板变量版本
 * @tparam T 待检查类型
 * @see IsUnsigned
 * @see not_unsigned
 */
template< typename T >
constexpr auto is_unsigned = bool_constant< IsUnsigned<T> >;

/**
 * @brief NotUnsigned 的模板变量版本
 * @tparam T 待检查类型
 * @see NotUnsigned
 * @see is_unsigned
 */
template< typename T >
constexpr auto not_unsigned = bool_constant< NotUnsigned<T> >;

#endif // defined(BR_CXX14)

} // namespace BR