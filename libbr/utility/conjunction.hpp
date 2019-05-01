/**
 * @file
 * @brief Conjunction - 逻辑合取
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conditional.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 逻辑合取，支持短路求值
 * @tparam TBooleans
 * @see ConjunctionByValue
 * @see conjunction
 */
template< typename... TBooleans >
struct Conjunction;

/**
 * @brief 逻辑合取，支持短路求值
 * @tparam values
 * @see Conjunction
 * @see conjunction_by_value
 */
template< bool... values >
struct ConjunctionByValue;

/**
 * @brief Conjunction 的模板变量版本
 * @tparam TBooleans
 * @see Conjunction
 */
template< typename... TBooleans >
constexpr auto conjunction = boolean_constant< Conjunction<TBooleans...> >;

/**
 * @brief ConjunctionByValue 的模板变量版本
 * @tparam values
 * @see ConjunctionByValue
 */
template< bool... values >
constexpr auto conjunction_by_value = boolean_constant< ConjunctionByValue<values...> >;

} // namespace Utility



inline namespace Utility {

template<>
struct Conjunction<> : public BooleanTrue {};

template< typename TB0 >
struct Conjunction<TB0> : public BooleanRewrap<TB0> {};

template< typename TB0, typename TB1, typename... TBn >
struct Conjunction< TB0, TB1, TBn... > : public Conditional< TB0, Conjunction< TB1, TBn... >, BooleanFalse > {};

template<>
struct ConjunctionByValue<> : public BooleanTrue {};

template< bool... TBn >
struct ConjunctionByValue< true, TBn... > : public BooleanConstant< ConjunctionByValue< TBn... >{} > {};

template< bool... TBn >
struct ConjunctionByValue< false, TBn... > : public BooleanFalse {};

} // namespace Utility

} // namespace BR
