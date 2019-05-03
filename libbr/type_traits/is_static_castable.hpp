/**
 * @file
 * @brief 静态类型转换检查
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/declare.hpp>

namespace BR {


inline namespace TypeTraits {

/**
 * @brief 检查 \em TFrom 是否能被静态转换为 \em TTo
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see Utility::IntegralConstant
 * @see NotStaticCastable
 *
 * 如果 \em TFrom 能被静态装换(\em static_cast)为 \em TTo ，那么封装的值为 \em true ；否则为 \em false
 */
template< typename TFrom, typename TTo >
struct IsStaticCastable;

/**
 * @brief IsStaticCastable 的否定
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see IsStaticCastable
 */
template< typename TFrom, typename TTo >
struct NotStaticCastable;

/**
 * @brief IsStaticCastable 的模板变量版本
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see IsStaticCastable
 * @see not_static_castable
 */
template< typename TFrom, typename TTo >
constexpr auto is_static_castable = boolean_constant< IsStaticCastable< TFrom, TTo > >;

/**
 * @brief NotStaticCastable 的模板变量版本
 * @tparam TFrom 被转换类型
 * @tparam TTo 转换目标类型
 * @see NotStaticCastable
 * @see is_static_castable
 */
template< typename TFrom, typename TTo >
constexpr auto not_static_castable = boolean_constant< NotStaticCastable< TFrom, TTo > >;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

struct IsStaticCastableTest {
	template< typename TFrom, typename TTo, typename = decltype(static_cast<TTo>(declare_rvalue<TFrom>())) >
	static BooleanTrue test(int);

	template< typename TFrom, typename TTo >
	static BooleanFalse test(...);
};

template< typename TFrom, typename TTo >
using IsStaticCastable = decltype(IsStaticCastableTest::test< TFrom, TTo >(0));

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename TFrom, typename TTo >
struct IsStaticCastable : BooleanRewrapPositive< _::TypeTraits::IsStaticCastable< TFrom, TTo > > {};

template< typename TFrom, typename TTo >
struct NotStaticCastable : BooleanRewrapNegative< _::TypeTraits::IsStaticCastable< TFrom, TTo > > {};

} // namespace TypeTraits

} // namespace BR