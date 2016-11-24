/**
 * @file
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_traits/conditional.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief 布尔常量封装类逻辑或
 * @tparam TBooleans
 * @see BooleanOrByValue
 * @see boolean_or
 */
template< typename... TBooleans >
struct BooleanOr;

/**
 * @brief 布尔常量逻辑或
 * @tparam values
 * @see BooleanOr
 * @see boolean_or_by_value
 */
template< bool... values >
struct BooleanOrByValue;

/**
 * @brief alias of BooleanOr
 * @tparam TBooleans
 * @see BooleanOr
 */
template< typename... TBooleans >
using Disjunction = BooleanOr<TBooleans...>;

#if defined(BR_AFTER_CXX11)

/**
 * @brief boolean_or
 * @tparam TBooleans
 * @see BooleanOr
 */
template< typename... TBooleans >
constexpr auto boolean_or = boolean_constant< BooleanOr<TBooleans...> >;

/**
 * @brief boolean_or_by_value
 * @tparam values
 * @see BooleanOrByValue
 */
template< bool... values >
constexpr auto boolean_or_by_value = boolean_constant< BooleanOrByValue<values...> >;

/**
 * @brief disjunction
 * @tparam TBooleans
 * @see Disjunction
 */
template< typename... TBooleans >
constexpr auto disjunction = boolean_constant< Disjunction<TBooleans...> >;

#endif // defined(BR_AFTER_CXX11)

} // namespace TypeTraits



inline namespace TypeTraits {

template<>
struct BooleanOr<> : public BooleanFalse {};

template< typename TB0 >
struct BooleanOr<TB0> : public BooleanRewrap<TB0> {};

template< typename TB0, typename TB1, typename... TBn >
struct BooleanOr< TB0, TB1, TBn... > : public Conditional< TB0, BooleanTrue, BooleanOr< TB1, TBn... > > {};

template<>
struct BooleanOrByValue<> : public BooleanFalse {};

template< bool... TBn >
struct BooleanOrByValue< true, TBn... > : public BooleanTrue {};

template< bool... TBn >
struct BooleanOrByValue< false, TBn... > : public BooleanConstant< BooleanOrByValue< TBn... >{} > {};

} // namespace TypeTraits

} // namespace BR
