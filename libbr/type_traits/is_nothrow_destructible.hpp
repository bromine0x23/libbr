/**
 * @file
 * @brief 检查类型是否可被 \em nothrow 地析构
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/remove_all_extents.hpp>
#include <libbr/type_traits/is_array.hpp>
#include <libbr/type_traits/is_function.hpp>
#include <libbr/type_traits/is_object.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/is_scalar.hpp>
#include <libbr/type_traits/is_void.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

struct IsNothrowDestructibleTest {
	template< typename T >
	static BooleanConstant< noexcept(make_reference<T>().~T()) > test(T *);

	template< typename T >
	static BooleanFalse test(...);
};

template< typename T >
using IsNothrowDestructibleBasic = decltype(IsNothrowDestructibleTest::test<T>(nullptr));

template< typename T >
using IsNothrowDestructible = BooleanAnd<
	NotVoid<T>,
	NotArrayUnknownBounds<T>,
	NotFunction<T>,
	BooleanOr<
		IsReference<T>,
		IsScalar<T>,
		IsNothrowDestructibleBasic<T>
	>
>;

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 检查 \em T 是否可被 \em nothrow 地析构
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see IsDestructible
 * @see NotNothrowDestructible
 *
 * 如果 \em T 可被 \em nothrow 地析构，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsNothrowDestructible : BooleanRewrapPositive< Detail::TypeOperate::IsNothrowDestructible<T> > {};

/**
 * @brief IsNothrowDestructible 的否定
 * @tparam T 待检查类型
 * @see IsNothrowDestructible
 */
template< typename T >
struct NotNothrowDestructible : BooleanRewrapNegative< Detail::TypeOperate::IsNothrowDestructible<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsNothrowDestructible 的模板变量版本
 * @tparam T 待检查类型
 * @see IsNothrowDestructible
 * @see not_nothrow_destructible
 */
template< typename T >
constexpr auto is_nothrow_destructible = bool_constant< IsNothrowDestructible<T> >;

/**
 * @brief NotNothrowDestructible 的模板变量版本
 * @tparam T 待检查类型
 * @see NotNothrowDestructible
 * @see is_nothrow_destructible
 */
template< typename T >
constexpr auto not_nothrow_destructible = bool_constant< NotNothrowDestructible<T> >;

#endif // defined(BR_CXX14)

} // namespace BR