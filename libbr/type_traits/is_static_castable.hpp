/**
 * @file
 * @brief 静态类型转换检查
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {

struct IsStaticCastableTest {
	template< typename TFrom, typename TTo, typename = decltype(static_cast<TTo>(make_rvalue<TFrom>())) >
	static BooleanTrue test(int);

	template< typename TFrom, typename TTo >
	static BooleanFalse test(...);
};

template< typename TFrom, typename TTo >
using IsStaticCastable = decltype(IsStaticCastableTest::test< TFrom, TTo >(0));

} // namespace TypeTraits
} // namespace Detail

/**
 * @brief 检查 \em TFrom 是否能被静态转换为 \em TTo
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see IntegerConstant
 * @see NotStaticCastable
 *
 * 如果 \em TFrom 能被静态装换(\em static_cast)为 \em TTo ，那么封装的值为 \em true ；否则为 \em false
 */
template< typename TFrom, typename TTo >
struct IsStaticCastable : BooleanRewrapPositive< Detail::TypeTraits::IsStaticCastable< TFrom, TTo > > {};

/**
 * @brief IsStaticCastable 的否定
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see IsStaticCastable
 */
template< typename TFrom, typename TTo >
struct NotStaticCastable : BooleanRewrapNegative< Detail::TypeTraits::IsStaticCastable< TFrom, TTo > > {};

#if defined(BR_CXX14)

/**
 * @brief IsStaticCastable 的模板变量版本
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see IsStaticCastable
 * @see not_static_castable
 */
template< typename TFrom, typename TTo >
constexpr auto is_static_castable = bool_constant< IsStaticCastable< TFrom, TTo > >;

/**
 * @brief NotStaticCastable 的模板变量版本
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see NotStaticCastable
 * @see is_static_castable
 */
template< typename TFrom, typename TTo >
constexpr auto not_static_castable = bool_constant< NotStaticCastable< TFrom, TTo > >;

#endif // defined(BR_CXX14)

} // namespace BR