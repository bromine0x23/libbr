/**
 * @file
 * @brief 类型转换检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_IS_CONVERTIBLE)
#  include <libbr/type_operate/bool.hpp>
#  include <libbr/type_traits/is_array.hpp>
#  include <libbr/type_traits/is_function.hpp>
#  include <libbr/type_traits/is_void.hpp>
#  include <libbr/utility/make_value.hpp>
#endif // !BR_IS_CONVERTIBLE

namespace BR {

/**
 * @brief 检查 \em TFrom 是否能转换为 \em TTo
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see BR::IntegerConstant
 * @see BR_IS_CONVERTIBLE
 * @see BR::NotConvertible
 *
 * 如果一个 \em TFrom 的右值能用在返回 \em TTo 类型的函数的返回语句中，即 \em TFrom 能被隐式装换为 \em TTo
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename TFrom, typename TTo >
struct IsConvertible;

/**
 * @brief IsConvertible 的否定
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see BR::IsConvertible
 */
template< typename TFrom, typename TTo >
struct NotConvertible;

#if defined(BR_CXX14)

/**
 * @brief IsConvertible 的模板变量版本
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see BR::IsConvertible
 * @see BR::not_convertible
 */
template< typename TFrom, typename TTo >
constexpr auto is_convertible = bool_constant< IsConvertible< TFrom, TTo > >;

/**
 * @brief NotConvertible 的模板变量版本
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see BR::NotConvertible
 * @see BR::is_convertible
 */
template< typename TFrom, typename TTo >
constexpr auto not_convertible = bool_constant< NotConvertible< TFrom, TTo > >;

#endif // defined(BR_CXX14)



namespace Detail {
namespace TypeTraits {

#if defined(BR_IS_CONVERTIBLE)

template< typename TFrom, typename TTo >
using IsConvertible = BooleanConstant< BR_IS_CONVERTIBLE(TFrom, TTo) >;

#else

struct IsConvertibleTest {
	template< typename T >
	static void test_aux(T);

	template< typename TFrom, typename TTo >
	static auto test(int) -> decltype((test_aux<TTo>(make_rvalue<TFrom>()), BooleanTrue()));

	template< typename TFrom, typename TTo >
	static auto test(...) -> BooleanFalse;
};

template< typename TFrom, typename TTo >
struct IsConvertibleBasic : public decltype(IsConvertibleTest::test< TFrom, TTo >(0)) {};

template< typename TFrom, typename TTo >
using IsConvertible = BooleanAnd<
	NotArray<TTo>,
	NotFunction<TTo>,
	BooleanOr<
		IsVoid<TTo>,
		BooleanAnd<
			NotVoid<TFrom>,
			IsConvertibleBasic< TFrom, TTo >
		>
	>
>;

#endif // BR_IS_CONVERTIBLE

} // namespace TypeTraits
} // namespace Detail

template< typename TFrom, typename TTo >
struct IsConvertible : BooleanRewrapPositive< Detail::TypeTraits::IsConvertible< TFrom, TTo > > {};

template< typename TFrom, typename TTo >
struct NotConvertible : BooleanRewrapNegative< Detail::TypeTraits::IsConvertible< TFrom, TTo > > {};

} // namespace BR
