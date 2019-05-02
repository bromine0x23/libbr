/**
 * @file
 * @brief NonDisjunction - 逻辑或非（NOR）
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conditional.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 逻辑或非（NOR），支持短路求值
 * @tparam TBooleans
 * @see NonDisjunctionByValue
 * @see non_disjunction
 */
template< typename... TBooleans >
struct NonDisjunction;

/**
 * @brief 逻辑或非（NOR），支持短路求值
 * @tparam values
 * @see NonDisjunction
 * @see non_disjunction_by_value
 */
template< Boolean... values >
struct NonDisjunctionByValue;

/**
 * @brief NonDisjunction 的模板变量版本
 * @tparam TBooleans
 * @see NonDisjunction
 */
template< typename... TBooleans >
constexpr auto non_disjunction = boolean_constant< NonDisjunction<TBooleans...> >;

/**
 * @brief NonDisjunctionByValue 的模板变量版本
 * @tparam values
 * @see NonDisjunctionByValue
 */
template< Boolean... values >
constexpr auto non_disjunction_by_value = boolean_constant< NonDisjunctionByValue<values...> >;

} // namespace Utility



namespace _ {
namespace Utility {

template< typename... TBs >
struct NonDisjunctionBasic;

template<>
struct NonDisjunctionBasic<> : public BooleanTrue {};

template< typename TB0, typename... TBn >
struct NonDisjunctionBasic< TB0, TBn... > : public Conditional< TB0, BooleanFalse, NonDisjunctionBasic< TBn... > > {};

template< Boolean... values >
struct NonDisjunctionByValueBasic;

template<>
struct NonDisjunctionByValueBasic<> : public BooleanTrue {};

template< Boolean... values >
struct NonDisjunctionByValueBasic< true, values... > : public BooleanFalse {};

template< Boolean... values >
struct NonDisjunctionByValueBasic< false, values... > : public BooleanConstant< NonDisjunctionByValueBasic<values...>{} > {};


template< typename... TBs >
struct NonDisjunction : public NonDisjunctionBasic<TBs...> {};

template< typename TB >
struct NonDisjunction<TB> : public BooleanRewrap<TB> {};

template< Boolean... values >
struct NonDisjunctionByValue : public NonDisjunctionByValueBasic<values...> {};

template< Boolean value >
struct NonDisjunctionByValue<value> : public BooleanConstant<value> {};

} // namespace Utility
} // namespace _

inline namespace Utility {

template< typename... TBooleans >
struct NonDisjunction : public BooleanRewrapPositive< _::Utility::NonDisjunction<TBooleans...> > {};

template< Boolean... values >
struct NonDisjunctionByValue : public BooleanRewrapPositive< _::Utility::NonDisjunctionByValue<values...> > {};

} // namespace Utility

} // namespace BR
