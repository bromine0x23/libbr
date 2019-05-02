/**
 * @file
 * @brief Implication - 实质蕴涵
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conditional.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 实质蕴涵
 * @tparam TP, TQ
 * @see ImplicationByValue
 * @see implication
 */
template< typename TP, typename TQ >
struct Implication;

/**
 * @brief 实质蕴涵
 * @tparam p, q
 * @see Implication
 * @see implication_by_value
 */
template< Boolean p, Boolean q >
struct ImplicationByValue;

/**
 * @brief Implication 的模板变量版本
 * @tparam TP, TQ
 * @see Implication
 */
template< typename TP, typename TQ >
constexpr auto implication = boolean_constant< Implication<TP, TQ> >;

/**
 * @brief ImplicationByValue 的模板变量版本
 * @tparam p, q
 * @see ImplicationByValue
 */
template< Boolean p, Boolean q >
constexpr auto implication_by_value = boolean_constant< ImplicationByValue<p, q> >;

} // namespace Utility



inline namespace Utility {

template< typename TP, typename TQ >
struct Implication : public Conditional< TP, BooleanRewrapPositive<TQ>, BooleanTrue > {};

template< Boolean p, Boolean q >
struct ImplicationByValue : public BooleanTrue {};

template<>
struct ImplicationByValue<true, false> : public BooleanFalse {};

} // namespace Utility

} // namespace BR
