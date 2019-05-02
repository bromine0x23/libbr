/**
 * @file
 * @brief Disjunction - 逻辑或（OR）
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conditional.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 逻辑或（OR），支持短路求值
 * @tparam TBooleans
 * @see DisjunctionByValue
 * @see disjunction
 */
template< typename... TBooleans >
struct Disjunction;

/**
 * @brief 逻辑或（OR），支持短路求值
 * @tparam values
 * @see Disjunction
 * @see disjunction_by_value
 */
template< Boolean... values >
struct DisjunctionByValue;

/**
 * @brief Disjunction 的模板变量版本
 * @tparam TBooleans
 * @see Disjunction
 */
template< typename... TBooleans >
constexpr auto disjunction = boolean_constant< Disjunction<TBooleans...> >;

/**
 * @brief DisjunctionByValue 的模板变量版本
 * @tparam values
 * @see DisjunctionByValue
 */
template< Boolean... values >
constexpr auto disjunction_by_value = boolean_constant< DisjunctionByValue<values...> >;

} // namespace Utility



namespace _ {
namespace Utility {

template< typename... TBs >
struct DisjunctionBasic;

template<>
struct DisjunctionBasic<> : public BooleanFalse {};

template< typename TB0, typename... TBn >
struct DisjunctionBasic< TB0, TBn... > : public Conditional< TB0, BooleanTrue, DisjunctionBasic< TBn... > > {};

template< Boolean... values >
struct DisjunctionByValueBasic;

template<>
struct DisjunctionByValueBasic<> : public BooleanFalse {};

template< Boolean... values >
struct DisjunctionByValueBasic< true, values... > : public BooleanTrue {};

template< Boolean... values >
struct DisjunctionByValueBasic< false, values... > : public BooleanConstant< DisjunctionByValueBasic<values...>{} > {};


template< typename... TBs >
struct Disjunction : public DisjunctionBasic<TBs...> {};

template< typename TB >
struct Disjunction<TB> : public BooleanRewrap<TB> {};

template< Boolean... values >
struct DisjunctionByValue : public DisjunctionByValueBasic<values...> {};

template< Boolean value >
struct DisjunctionByValue<value> : public BooleanConstant<value> {};

} // namespace Utility
} // namespace _

inline namespace Utility {

template< typename... TBooleans >
struct Disjunction : public BooleanRewrapPositive< _::Utility::Disjunction<TBooleans...> > {};

template< Boolean... values >
struct DisjunctionByValue : public BooleanRewrapPositive< _::Utility::DisjunctionByValue<values...> > {};

} // namespace Utility

} // namespace BR
