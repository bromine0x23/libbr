/**
 * @file
 * @author Bromine0x23
 * @since 2016/11/23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/conditional.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 布尔常量封装类逻辑与
 * @tparam TBooleans
 * @see BooleanAndByValue
 * @see boolean_and
 */
template< typename... TBooleans >
struct BooleanAnd;

/**
 * @brief 布尔常量逻辑与
 * @tparam values
 * @see BooleanAnd
 * @see boolean_and_by_value
 */
template< bool... values >
struct BooleanAndByValue;

/**
 * @brief alias of BooleanAnd
 * @tparam TBooleans
 * @see BooleanAnd
 */
template< typename... TBooleans >
using Conjunction = BooleanAnd<TBooleans...>;

#if defined(BR_AFTER_CXX11)

/**
 * @brief boolean_and
 * @tparam TBooleans
 * @see BooleanAnd
 */
template< typename... TBooleans >
constexpr auto boolean_and = boolean_constant< BooleanAnd<TBooleans...> >;

/**
 * @brief boolean_and_by_value
 * @tparam values
 * @see BooleanAndByValue
 */
template< bool... values >
constexpr auto boolean_and_by_value = boolean_constant< BooleanAndByValue<values...> >;

/**
 * @brief conjunction
 * @tparam TBooleans
 * @see Conjunction
 */
template< typename... TBooleans >
constexpr auto conjunction = boolean_constant< Conjunction<TBooleans...> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



inline namespace TypeTraits {

template<>
struct BooleanAnd<> : public BooleanTrue {};

template< typename TB0 >
struct BooleanAnd<TB0> : public BooleanRewrap<TB0> {};

template< typename TB0, typename TB1, typename... TBn >
struct BooleanAnd< TB0, TB1, TBn... > : public Conditional< TB0, BooleanAnd< TB1, TBn... >, BooleanFalse > {};

template<>
struct BooleanAndByValue<> : public BooleanTrue {};

template< bool... TBn >
struct BooleanAndByValue< true, TBn... > : public BooleanConstant< BooleanAndByValue< TBn... >{} > {};

template< bool... TBn >
struct BooleanAndByValue< false, TBn... > : public BooleanFalse {};

} // namespace TypeTraits

} // namespace BR
