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
template< typename TB >
using Boolean = BooleanConstant< TB::value >;

/**
 * @brief 封装否定值
 */
template< typename TB >
using BooleanNot = BooleanConstant< !TB::value >;

/**
 * @brief 布尔常量封装类逻辑与
 */
template< typename... >
struct BooleanAnd;

template<>
struct BooleanAnd<> : BooleanTrue {};

template< typename TB0 >
struct BooleanAnd<TB0> : Boolean<TB0> {};

template< typename TB0, typename TB1, typename... TBn >
struct BooleanAnd< TB0, TB1, TBn... > : Conditional< TB0, BooleanAnd< TB1, TBn... >, BooleanFalse > {};

/**
 * @brief 布尔常量封装类逻辑或
 */
template< typename... >
struct BooleanOr;

template<>
struct BooleanOr<> : BooleanFalse {};

template< typename TB0 >
struct BooleanOr<TB0> : Boolean<TB0> {};

template< typename TB0, typename TB1, typename... TBn >
struct BooleanOr< TB0, TB1, TBn... > : Conditional< TB0, BooleanTrue, BooleanOr< TB1, TBn... > > {};

/**
 * @brief 封装布尔常量列表
 */
template< bool... TBn >
using Booleans = Integers< bool, TBn... >;

/**
 * @brief 布尔常量逻辑与
 */
template< bool... >
struct BooleanAndByValue;

template<>
struct BooleanAndByValue<> : BooleanTrue {};

template< bool... TBn >
struct BooleanAndByValue< true, TBn... > : BooleanConstant< BooleanAndByValue< TBn... >::value > {};

template< bool... TBn >
struct BooleanAndByValue< false, TBn... > : BooleanFalse {};

/**
 * @brief 布尔常量逻辑或
 */
template< bool... >
struct BooleanOrByValue;

template<>
struct BooleanOrByValue<> : BooleanFalse {};

template< bool... TBn >
struct BooleanOrByValue< true, TBn... > : BooleanTrue {};

template< bool... TBn >
struct BooleanOrByValue< false, TBn... > : BooleanConstant< BooleanOrByValue< TBn... >::value > {};

} // namespace BR
