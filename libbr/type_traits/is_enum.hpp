/**
 * @file
 * @brief 枚举类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_ENUM)
#  include <libbr/type_operate/add_lvalue_reference.hpp>
#  include <libbr/type_operate/bool.hpp>
#  include <libbr/type_traits/is_arithmetic.hpp>
#  include <libbr/type_traits/is_array.hpp>
#  include <libbr/type_traits/is_class.hpp>
#  include <libbr/type_traits/is_convertible.hpp>
#  include <libbr/type_traits/is_reference.hpp>
#  include <libbr/type_traits/is_union.hpp>
#  include <libbr/type_traits/is_void.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeTraits {

using BR::RemoveConstVolatile;

#if defined(BR_IS_ENUM)

template< typename T >
using IsEnumBasic = BooleanConstant< BR_IS_ENUM(T) >;

#else

struct IntConvertible {
	IntConvertible(int);
};

template< typename T >
using IsEnumBasic = BooleanAnd<
	NotVoid<T>,
	NotArithmetic<T>,
	NotReference<T>,
	NotClass<T>,
	NotUnion<T>,
	NotArray<T>,
	IsConvertible<
		AddLValueReference<T>,
		IntConvertible
	>
>;

#endif // defined(BR_IS_ENUM)

template< typename T >
using IsEnum = IsEnumBasic< RemoveConstVolatile<T> >;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否是枚举类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotEnum
 *
 * 如果 \em T 是枚举类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsEnum : BooleanRewrapPositive< Detail::TypeTraits::IsEnum<T> > {};

/**
 * @brief IsEnum 的否定
 * @tparam T 待检查类型
 * @see IsEnum
 */
template< typename T >
struct NotEnum : BooleanRewrapNegative< Detail::TypeTraits::IsEnum<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsEnum 的模板变量版本
 * @tparam T 待检查类型
 * @see IsEnum
 * @see not_enum
 */
template< typename T >
constexpr auto is_enum = bool_constant< IsEnum<T> >;

/**
 * @brief NotEnum 的模板变量版本
 * @tparam T 待检查类型
 * @see NotEnum
 * @see is_enum
 */
template< typename T >
constexpr auto not_enum = bool_constant< NotEnum<T> >;

#endif // defined(BR_CXX14)

} // namespace BR
