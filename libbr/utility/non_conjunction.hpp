/**
 * @file
 * @brief NonConjunction - 逻辑与非（NAND）
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conditional.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 逻辑与非（NAND），支持短路求值
 * @tparam TBooleans
 * @see NonConjunctionByValue
 * @see non_conjunction
 */
template< typename... TBooleans >
struct NonConjunction;

/**
 * @brief 逻辑与非（NAND），支持短路求值
 * @tparam values
 * @see NonConjunction
 * @see non_conjunction_by_value
 */
template< Boolean... values >
struct NonConjunctionByValue;

/**
 * @brief NonConjunction 的模板变量版本
 * @tparam TBooleans
 * @see NonConjunction
 */
template< typename... TBooleans >
constexpr auto non_conjunction = boolean_constant< NonConjunction<TBooleans...> >;

/**
 * @brief NonConjunctionByValue 的模板变量版本
 * @tparam values
 * @see NonConjunctionByValue
 */
template< Boolean... values >
constexpr auto non_conjunction_by_value = boolean_constant< NonConjunctionByValue<values...> >;

} // namespace Utility



namespace _ {
namespace Utility {

template< typename... TBs >
struct NonConjunctionBasic;

template<>
struct NonConjunctionBasic<> : public BooleanFalse {};

template< typename TB0, typename... TBn >
struct NonConjunctionBasic< TB0, TBn... > : public Conditional< TB0, NonConjunctionBasic< TBn... >, BooleanTrue > {};

template< Boolean... values >
struct NonConjunctionByValueBasic;

template<>
struct NonConjunctionByValueBasic<> : public BooleanFalse {};

template< Boolean... values >
struct NonConjunctionByValueBasic< true, values... > : public BooleanConstant< NonConjunctionByValueBasic<values...>{} > {};

template< Boolean... values >
struct NonConjunctionByValueBasic< false, values... > : public BooleanTrue {};


template< typename... TBs >
struct NonConjunction : public NonConjunctionBasic<TBs...> {};

template< typename TB >
struct NonConjunction<TB> : public BooleanRewrap<TB> {};

template< Boolean... values >
struct NonConjunctionByValue : public NonConjunctionByValueBasic<values...> {};

template< Boolean value >
struct NonConjunctionByValue<value> : public BooleanConstant<value> {};

} // namespace Utility
} // namespace _

inline namespace Utility {

template< typename... TBooleans >
struct NonConjunction : public BooleanRewrapPositive< _::Utility::NonConjunction<TBooleans...> > {};

template< Boolean... values >
struct NonConjunctionByValue : public BooleanRewrapPositive< _::Utility::NonConjunctionByValue<values...> > {};

} // namespace Utility

} // namespace BR
