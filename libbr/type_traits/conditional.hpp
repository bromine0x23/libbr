/**
 * @file
 * @brief 编译期条件语句模拟
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 选择性启用一种函数重载或模板特化
 * @tparam condition 条件
 * @tparam TWhenTrue \em condition 为 \em true 时的结果类型
 * @tparam TWhenFalse \em condition 为 \em false 时的结果类型
 *
 * 如果 \em condition为 \em true，则包装有类型 \em TWhenTrue ；否则包装有类型 \em TWhenFalse
 */
template< bool condition, typename TWhenTrue, typename TWhenFalse = void >
struct TypeConditionalByValue;

/**
 * @brief TypeConditionalByValue 的简写版本
 * @tparam condition 条件
 * @tparam TWhenTrue \em condition 为 \em true 时的结果类型
 * @tparam TWhenFalse \em condition 为 \em false 时的结果类型
 * @see TypeConditionalByValue
 */
template< bool condition, typename TWhenTrue, typename TWhenFalse = void >
using ConditionalByValue = TypeUnwrap< TypeConditionalByValue< condition, TWhenTrue, TWhenFalse > >;

/**
 * @brief TypeConditionalByValue 使用布尔常量包装类的版本
 * @tparam TCondition 条件
 * @tparam TWhenTrue \em condition 为 \em true 时的结果类型
 * @tparam TWhenFalse \em condition 为 \em false 时的结果类型
 * @see TypeConditionalByValue
 */
template< typename TCondition, typename TWhenTrue, typename TWhenFalse = void >
using TypeConditional = TypeConditionalByValue< TCondition::value, TWhenTrue, TWhenFalse >;

/**
 * @brief TypeConditional 的简写版本
 * @tparam TCondition 条件
 * @tparam TWhenTrue \em condition 为 \em true 时的结果类型
 * @tparam TWhenFalse \em condition 为 \em false 时的结果类型
 * @see TypeConditional
 */
template< typename TCondition, typename TWhenTrue, typename TWhenFalse = void >
using Conditional = TypeUnwrap< TypeConditional< TCondition, TWhenTrue, TWhenFalse > >;

} // namespace TypeTraits



inline namespace TypeTraits {

template< typename TWhenTrue, typename TWhenFalse >
struct TypeConditionalByValue< true, TWhenTrue, TWhenFalse > : public TypeWrapper<TWhenTrue> {};

template< typename TWhenTrue, typename TWhenFalse >
struct TypeConditionalByValue< false, TWhenTrue, TWhenFalse > : public TypeWrapper<TWhenFalse> {};

} // namespace TypeTraits

} // namespace BR