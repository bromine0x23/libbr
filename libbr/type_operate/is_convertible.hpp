/**
 * @file
 * @brief 类型转换检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_IS_CONVERTIBLE)
#  include <libbr/type_operate/is_array.hpp>
#  include <libbr/type_operate/is_function.hpp>
#  include <libbr/type_operate/is_void.hpp>
#  include <libbr/utility/make_value.hpp>
#endif // !BR_IS_CONVERTIBLE

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_CONVERTIBLE)

template< typename TFrom, typename TTo >
using IsConvertible = BoolConstant< BR_IS_CONVERTIBLE(TFrom, TTo) >;

#else

struct IsConvertibleTest {
	template< typename T >
	static void test_aux(T);

	template< typename TFrom, typename TTo >
	static decltype((test_aux<TTo>(make_rvalue<TFrom>()), BooleanTrue())) test(int);

	template< typename TFrom, typename TTo >
	static BooleanFalse test(...);
};

template< typename TFrom, typename TTo >
using IsConvertibleBasic = decltype(IsConvertibleTest::test< TFrom, TTo >(0));


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

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em TFrom 是否能转换为 \em TTo
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see IntegerConstant
 * @see NotConvertible
 *
 * 如果一个 \em TFrom 的右值能用在返回 \em TTo 类型的函数的返回语句中，即 \em TFrom 能被隐式装换为 \em TTo
 * 那么封装的值为 \em true ；否则为 \em false
 */
template< typename TFrom, typename TTo >
struct IsConvertible : Boolean< Detail::TypeOperate::IsConvertible< TFrom, TTo > > {};

/**
 * @brief IsConvertible 的否定
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see IsConvertible
 */
template< typename TFrom, typename TTo >
struct NotConvertible : BooleanNot< Detail::TypeOperate::IsConvertible< TFrom, TTo > > {};

#if defined(BR_CXX14)

/**
 * @brief IsConvertible 的模板变量版本
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see IsConvertible
 * @see not_convertible
 */
template< typename TFrom, typename TTo >
constexpr auto is_convertible = IsConvertible< TFrom, TTo >::value;

/**
 * @brief NotConvertible 的模板变量版本
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see NotConvertible
 * @see is_convertible
 */
template< typename TFrom, typename TTo >
constexpr auto not_convertible = NotConvertible< TFrom, TTo >::value;

#endif // defined(BR_CXX14)

} // namespace BR
