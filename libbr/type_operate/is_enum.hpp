/**
 * @file
 * @brief 枚举类型检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#if !defined(BR_IS_ENUM)
#  include <libbr/type_operate/add_lvalue_reference.hpp>
#  include <libbr/type_operate/is_arithmetic.hpp>
#  include <libbr/type_operate/is_array.hpp>
#  include <libbr/type_operate/is_class.hpp>
#  include <libbr/type_operate/is_convertible.hpp>
#  include <libbr/type_operate/is_reference.hpp>
#  include <libbr/type_operate/is_union.hpp>
#  include <libbr/type_operate/is_void.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

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

} // namespace TypeOperate
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
struct IsEnum : Boolean< Detail::TypeOperate::IsEnum<T> > {};

/**
 * @brief IsEnum 的否定
 * @tparam T 待检查类型
 * @see IsEnum
 */
template< typename T >
struct NotEnum : BooleanNot< Detail::TypeOperate::IsEnum<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsEnum 的模板变量版本
 * @tparam T 待检查类型
 * @see IsEnum
 * @see not_enum
 */
template< typename T >
constexpr auto is_enum = IsEnum<T>::value;

/**
 * @brief NotEnum 的模板变量版本
 * @tparam T 待检查类型
 * @see NotEnum
 * @see is_enum
 */
template< typename T >
constexpr auto not_enum = NotEnum<T>::value;

#endif // defined(BR_CXX14)

} // namespace BR
