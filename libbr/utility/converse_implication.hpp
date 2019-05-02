/**
 * @file
 * @brief ConverseImplication - 反蕴涵
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conditional.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 反蕴涵
 * @tparam TP, TQ
 * @see ConverseImplicationByValue
 * @see converse_implication
 */
template< typename TP, typename TQ >
struct ConverseImplication;

/**
 * @brief 反蕴涵
 * @tparam p, q
 * @see ConverseImplication
 * @see converse_implication_by_value
 */
template< Boolean p, Boolean q >
struct ConverseImplicationByValue;

/**
 * @brief ConverseImplication 的模板变量版本
 * @tparam TP, TQ
 * @see ConverseImplication
 */
template< typename TP, typename TQ >
constexpr auto converse_implication = boolean_constant< ConverseImplication<TP, TQ> >;

/**
 * @brief ConverseImplicationByValue 的模板变量版本
 * @tparam p, q
 * @see ConverseImplicationByValue
 */
template< Boolean p, Boolean q >
constexpr auto converse_implication_by_value = boolean_constant< ConverseImplicationByValue<p, q> >;

} // namespace Utility



inline namespace Utility {

template< typename TP, typename TQ >
struct ConverseImplication : public Conditional< TP, BooleanTrue, BooleanRewrapNegative<TQ> > {};

template< Boolean p, Boolean q >
struct ConverseImplicationByValue : public BooleanTrue {};

template<>
struct ConverseImplicationByValue<false, true> : public BooleanFalse {};

} // namespace Utility

} // namespace BR
