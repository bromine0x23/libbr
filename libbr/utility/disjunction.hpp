/**
 * @file
 * @brief Disjunction - 逻辑析取
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conditional.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 逻辑析取，支持短路求值
 * @tparam TBooleans
 * @see DisjunctionByValue
 * @see disjunction
 */
template< typename... TBooleans >
struct Disjunction;

/**
 * @brief 布尔常量逻辑或
 * @tparam values
 * @see Disjunction
 * @see disjunction_by_value
 */
template< bool... values >
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
template< bool... values >
constexpr auto disjunction_by_value = boolean_constant< DisjunctionByValue<values...> >;

} // namespace Utility



inline namespace Utility {

template< typename TB0, typename TB1, typename... TBn >
struct Disjunction< TB0, TB1, TBn... > : public Conditional< TB0, BooleanTrue, Disjunction< TB1, TBn... > > {};

template< typename TB0 >
struct Disjunction<TB0> : public BooleanRewrap<TB0> {};

template<>
struct Disjunction<> : public BooleanFalse {};

template< bool... TBn >
struct DisjunctionByValue< true, TBn... > : public BooleanTrue {};

template< bool... TBn >
struct DisjunctionByValue< false, TBn... > : public BooleanConstant< DisjunctionByValue< TBn... >{} > {};

template<>
struct DisjunctionByValue<> : public BooleanFalse {};

} // namespace Utility

} // namespace BR
