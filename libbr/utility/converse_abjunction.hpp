/**
 * @file
 * @brief ConverseAbjunction - 反非蕴涵
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conditional.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 反非蕴涵
 * @tparam TP, TQ
 * @see ConverseAbjunctionByValue
 * @see converse_abjunction
 */
template< typename TP, typename TQ >
struct ConverseAbjunction;

/**
 * @brief 反非蕴涵
 * @tparam p, q
 * @see ConverseAbjunction
 * @see converse_abjunction_by_value
 */
template< Boolean p, Boolean q >
struct ConverseAbjunctionByValue;

/**
 * @brief Abjunction 的模板变量版本
 * @tparam TP, TQ
 * @see ConverseAbjunction
 */
template< typename TP, typename TQ >
constexpr auto converse_abjunction = boolean_constant< ConverseAbjunction<TP, TQ> >;

/**
 * @brief AbjunctionByValue 的模板变量版本
 * @tparam p, q
 * @see ConverseAbjunctionByValue
 */
template< Boolean p, Boolean q >
constexpr auto converse_abjunction_by_value = boolean_constant< ConverseAbjunctionByValue<p, q> >;

} // namespace Utility



inline namespace Utility {

template< typename TP, typename TQ >
struct ConverseAbjunction : public Conditional< TP, BooleanFalse, BooleanRewrapPositive<TQ> > {};

template< Boolean p, Boolean q >
struct ConverseAbjunctionByValue : public BooleanFalse {};

template<>
struct ConverseAbjunctionByValue<false, true> : public BooleanTrue {};

} // namespace Utility

} // namespace BR
