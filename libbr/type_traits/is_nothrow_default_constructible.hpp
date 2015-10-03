/**
 * @file
 * @brief 检查类型是否可被 \em nothrow 地默认构造
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/remove_all_extents.hpp>
#include <libbr/type_traits/is_array.hpp>
#include <libbr/type_traits/is_default_constructible.hpp>
#include <libbr/type_traits/is_void.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

template< typename T >
struct IsNothrowDefaultConstructibleBasic : BooleanConstant< noexcept(T()) > {};

template< typename T >
using IsNothrowDefaultConstructible = BooleanAnd<
	IsDefaultConstructible<T>,
	Conditional<
		IsArray<T>,
		BooleanAnd<
			IsArrayKnownBounds<T>,
			IsNothrowDefaultConstructibleBasic< RemoveAllExtents<T> >
		>,
		IsNothrowDefaultConstructibleBasic<T>
	>
>;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否可被 \em nothrow 地默认构造
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsDefaultConstructible
 * @see NotNothrowDefaultConstructible
 *
 * 如果 \em T 可被 \em nothrow 地默认构造，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsNothrowDefaultConstructible : BooleanRewrapPositive< Detail::TypeTraits::IsNothrowDefaultConstructible<T> > {};

/**
 * @brief IsNothrowDefaultConstructible 的否定
 * @tparam T 待检查类型
 * @see IsNothrowDefaultConstructible
 */
template< typename T >
struct NotNothrowDefaultConstructible : BooleanRewrapNegative< Detail::TypeTraits::IsNothrowDefaultConstructible<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsNothrowDefaultConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @see IsNothrowDefaultConstructible
 * @see not_nothrow_default_constructible
 */
template< typename T >
constexpr auto is_nothrow_default_constructible = bool_constant< IsNothrowDefaultConstructible<T> >;

/**
 * @brief NotNothrowDefaultConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @see NotNothrowDefaultConstructible
 * @see is_nothrow_default_constructible
 */
template< typename T >
constexpr auto not_nothrow_default_constructible = bool_constant< NotNothrowDefaultConstructible<T> >;

#endif // defined(BR_CXX14)

} // namespace BR