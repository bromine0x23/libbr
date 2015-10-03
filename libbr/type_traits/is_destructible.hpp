/**
 * @file
 * @brief 检查类型是否可被析构
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
#include <libbr/type_traits/is_scalar.hpp>
#include <libbr/type_traits/is_void.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

struct IsDestructibleTester {
	template< typename T, typename = decltype(make_reference< T >().~T()) >
	static BooleanTrue test(T *);

	template< typename T >
	static BooleanFalse test(...);
};

template< typename T >
using IsDestructibleBasic = decltype(IsDestructibleTester::test<T>(nullptr));

template< typename T >
using IsDestructible = BooleanAnd<
	NotVoid<T>,
	NotArrayUnknownBounds<T>,
	NotFunction<T>,
	BooleanOr<
		IsReference<T>,
		IsScalar<T>,
		IsDestructibleBasic< RemoveAllExtents<T> >
	>
>;

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em T 是否可被析构
 * @tparam T 待检查类型
 * @see IntegerConstant
 * @see NotDestructible
 *
 * 如果 \em T 可被析构，那么封装的值为 \em true ；否则为 \em false
 */
template< typename T >
struct IsDestructible : BooleanRewrapPositive< Detail::TypeTraits::IsDestructible<T> > {};

/**
 * @brief IsDestructible 的否定
 * @tparam T 待检查类型
 * @see IsDestructible
 */
template< typename T >
struct NotDestructible : BooleanRewrapNegative< Detail::TypeTraits::IsDestructible<T> > {};

#if defined(BR_CXX14)

/**
 * @brief IsDestructible 的模板变量版本
 * @tparam T 待检查类型
 * @see IsDestructible
 * @see not_destructible
 */
template< typename T >
constexpr auto is_destructible = bool_constant< IsDestructible<T> >;

/**
 * @brief NotDestructible 的模板变量版本
 * @tparam T 待检查类型
 * @see NotDestructible
 * @see is_destructible
 */
template< typename T >
constexpr auto not_destructible = bool_constant< NotDestructible<T> >;

#endif // defined(BR_CXX14)

} // namespace BR