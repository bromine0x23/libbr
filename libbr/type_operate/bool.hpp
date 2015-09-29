/**
 * @file
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/utility/bool_constant.hpp>

namespace BR {

/**
 * @brief 重封装布尔常量
 */
template< typename B >
using Boolean = BooleanConstant< B::value >;

/**
 * @brief 封装否定值
 */
template< typename B >
using BooleanNot = BooleanConstant< !B::value >;

/**
 * @brief 布尔常量封装类逻辑与
 */
template< typename... >
struct BooleanAnd;

template<>
struct BooleanAnd<> : BooleanTrue {};

template< typename B0 >
struct BooleanAnd<B0> : Boolean<B0> {};

template< typename B0, typename B1, typename... Bn >
struct BooleanAnd< B0, B1, Bn... > : Conditional< B0, BooleanAnd< B1, Bn... >, BooleanFalse > {};

/**
 * @brief 布尔常量封装类逻辑或
 */
template< typename... >
struct BooleanOr;

template<>
struct BooleanOr<> : BooleanFalse {};

template< typename B0 >
struct BooleanOr<B0> : Boolean<B0> {};

template< typename B0, typename B1, typename... Bn >
struct BooleanOr< B0, B1, Bn... > : Conditional< B0, BooleanTrue, BooleanOr< B1, Bn... > > {};

/**
 * @brief 封装布尔常量列表
 */
template< bool... Bn >
using Booleans = Integers< bool, Bn... >;

/**
 * @brief 布尔常量逻辑与
 */
template< bool... >
struct BooleanAndByValue;

template<>
struct BooleanAndByValue<> : BooleanTrue {};

template< bool... Bn >
struct BooleanAndByValue< true, Bn... > : BooleanConstant< BooleanAndByValue< Bn... >::value > {};

template< bool... Bn >
struct BooleanAndByValue< false, Bn... > : BooleanFalse {};

/**
 * @brief 布尔常量逻辑或
 */
template< bool... >
struct BooleanOrByValue;

template<>
struct BooleanOrByValue<> : BooleanFalse {};

template< bool... Bn >
struct BooleanOrByValue< true, Bn... > : BooleanTrue {};

template< bool... Bn >
struct BooleanOrByValue< false, Bn... > : BooleanConstant< BooleanOrByValue< Bn... >::value > {};

} // namespace BR
