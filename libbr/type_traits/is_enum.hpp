/**
 * @file
 * @brief 枚举类型检查
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_ENUM)
#  include <libbr/type_traits/add_lvalue_reference.hpp>
#  include <libbr/type_traits/boolean.hpp>
#  include <libbr/type_traits/is_arithmetic.hpp>
#  include <libbr/type_traits/is_array.hpp>
#  include <libbr/type_traits/is_class.hpp>
#  include <libbr/type_traits/is_convertible.hpp>
#  include <libbr/type_traits/is_reference.hpp>
#  include <libbr/type_traits/is_union.hpp>
#  include <libbr/type_traits/is_void.hpp>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 检查 \em T 是否是枚举类型
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see BR_IS_ENUM
 * @see NotEnum
 *
 * 如果 \em T 是枚举类型，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsEnum;

/**
 * @brief IsEnum 的否定
 * @tparam T 待检查类型
 * @see IsEnum
 */
template< typename T >
struct NotEnum;

#if defined(BR_AFTER_CXX11)

/**
 * @brief IsEnum 的模板变量版本
 * @tparam T 待检查类型
 * @see IsEnum
 * @see not_enum
 */
template< typename T >
constexpr auto is_enum = boolean_constant< IsEnum<T> >;

/**
 * @brief NotEnum 的模板变量版本
 * @tparam T 待检查类型
 * @see NotEnum
 * @see is_enum
 */
template< typename T >
constexpr auto not_enum = boolean_constant< NotEnum<T> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_ENUM)

template< typename T >
using IsEnum = BooleanConstant< BR_IS_ENUM(T) >;

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

template< typename T >
using IsEnum = IsEnumBasic< RemoveConstVolatile<T> >;

#endif // defined(BR_IS_ENUM)

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IsEnum : public BooleanRewrapPositive< Detail::TypeTraits::IsEnum<T> > {};

template< typename T >
struct NotEnum : public BooleanRewrapNegative< Detail::TypeTraits::IsEnum<T> > {};

} // namespace TypeTraits

} // namespace BR
