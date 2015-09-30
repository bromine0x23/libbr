/**
 * @file
 * @brief 无符号整型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_integer.hpp>
#include <libbr/type_operate/is_enum.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsUnsignedBasic {
	using Type = RemoveConstVolatile<T>;
	constexpr static auto value = static_cast<Type>(-1) > static_cast<Type>(0);
};

template< typename T >
using IsUnsigned = BooleanAnd< BooleanOr< IsInteger<T>, IsEnum<T> >, BooleanConstant< IsUnsignedBasic<T>::value > >;

} // namespace TypeOperate
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
struct IsUnsigned : Boolean< Detail::TypeOperate::IsUnsigned<T> > {};

/**
 * @brief IsUnsigned 的否定
 * @tparam T 待检查类型
 * @see IsUnsigned
 */
template< typename T >
struct NotUnsigned : BooleanNot< Detail::TypeOperate::IsUnsigned<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsUnsigned 的模板变量版本
 * @tparam T 待检查类型
 * @see IsUnsigned
 * @see not_unsigned
 */
template< typename T >
constexpr auto is_unsigned = IsUnsigned<T>::value;

/**
 * @brief NotUnsigned 的模板变量版本
 * @tparam T 待检查类型
 * @see NotUnsigned
 * @see is_unsigned
 */
template< typename T >
constexpr auto not_unsigned = NotUnsigned<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR