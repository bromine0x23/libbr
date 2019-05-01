/**
 * @file
 * @brief Abjunction - 实质非蕴涵
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conditional.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 实质非蕴涵
 * @tparam TP, TQ
 * @see AbjunctionByValue
 * @see abjunction
 */
template< typename TP, typename TQ >
struct Abjunction;

/**
 * @brief 实质非蕴涵
 * @tparam p, q
 * @see Abjunction
 * @see abjunction_by_value
 */
template< Boolean p, Boolean q >
struct AbjunctionByValue;

/**
 * @brief Abjunction 的模板变量版本
 * @tparam TP, TQ
 * @see Abjunction
 */
template< typename TP, typename TQ >
constexpr auto abjunction = boolean_constant< Abjunction<TP, TQ> >;

/**
 * @brief AbjunctionByValue 的模板变量版本
 * @tparam p, q
 * @see AbjunctionByValue
 */
template< Boolean p, Boolean q >
constexpr auto abjunction_by_value = boolean_constant< AbjunctionByValue<p, q> >;

} // namespace Utility



inline namespace Utility {

template< typename TP, typename TQ >
struct Abjunction : public Conditional< TP, BooleanRewrapNegative<TQ>, BooleanFalse > {};

template< Boolean p, Boolean q >
struct AbjunctionByValue : public BooleanFalse {};

template<>
struct AbjunctionByValue<false, true> : public BooleanTrue {};

} // namespace Utility

} // namespace BR
