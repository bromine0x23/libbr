/**
 * @file
 * @brief 检查类型是否可被默认构造
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
#include <libbr/type_traits/is_void.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

struct IsDefaultConstructibleTester {
	template< typename T, typename = decltype(T()) >
	static BooleanTrue test(T *);

	template< typename T >
	static BooleanFalse test(...);
};

template< typename T >
using IsDefaultConstructibleBasic = BooleanAnd<
	NotVoid<T>,
	decltype(IsDefaultConstructibleTester::test<T>(nullptr))
>;

template< typename T >
using IsDefaultConstructible = Conditional<
	IsArray<T>,
	BooleanAnd<
		IsArrayKnownBounds<T>,
		IsDefaultConstructibleBasic< RemoveAllExtents<T> >
	>,
	IsDefaultConstructibleBasic<T>
>;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否可被默认构造
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotDefaultConstructible
 *
 * 如果 \em T 可被默认构造，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsDefaultConstructible : BooleanRewrapPositive< Detail::TypeTraits::IsDefaultConstructible<T> > {};

/**
 * @brief IsDefaultConstructible 的否定
 * @tparam T 待检查类型
 * @see IsDefaultConstructible
 */
template< typename T, typename ... TArguments >
struct NotDefaultConstructible : BooleanRewrapNegative< Detail::TypeTraits::IsDefaultConstructible<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsDefaultConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @see IsDefaultConstructible
 * @see not_default_constructible
 */
template< typename T >
constexpr auto is_default_constructible = bool_constant< IsDefaultConstructible<T> >;

/**
 * @brief NotDefaultConstructible 的模板变量版本
 * @tparam T 待检查类型
 * @see NotDefaultConstructible
 * @see is_default_constructible
 */
template< typename T >
constexpr auto not_default_constructible = bool_constant< NotDefaultConstructible<T> >;

#endif // defined(BR_CXX14)

} // namespace BR