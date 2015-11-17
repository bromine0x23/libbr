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
 * @brief 布尔常量封装类否定
 */
template< typename TB >
using BooleanNot = BooleanRewrapNegative<TB>;

/**
 * @brief 布尔常量封装类逻辑与
 */
template< typename... >
struct BooleanAnd;

template<>
struct BooleanAnd<> : public BooleanTrue {
};

template< typename TB0 >
struct BooleanAnd<TB0> : public BooleanRewrapPositive<TB0> {
};

template< typename TB0, typename TB1, typename... TBn >
struct BooleanAnd< TB0, TB1, TBn... > : public Conditional< TB0, BooleanAnd< TB1, TBn... >, BooleanFalse > {
};

/**
 * @brief 布尔常量封装类逻辑或
 */
template< typename... >
struct BooleanOr;

template<>
struct BooleanOr<> : public BooleanFalse {
};

template< typename TB0 >
struct BooleanOr<TB0> : public BooleanRewrapPositive<TB0> {
};

template< typename TB0, typename TB1, typename... TBn >
struct BooleanOr< TB0, TB1, TBn... > : public Conditional< TB0, BooleanTrue, BooleanOr< TB1, TBn... > > {
};

/**
 * @brief 布尔常量逻辑与
 */
template< bool... >
struct BooleanAndByValue;

template<>
struct BooleanAndByValue<> : public BooleanTrue {
};

template< bool... TBn >
struct BooleanAndByValue< true, TBn... > : public BooleanConstant< BooleanAndByValue< TBn... >::value > {
};

template< bool... TBn >
struct BooleanAndByValue< false, TBn... > : public BooleanFalse {
};

/**
 * @brief 布尔常量逻辑或
 */
template< bool... >
struct BooleanOrByValue;

template<>
struct BooleanOrByValue<> : public BooleanFalse {
};

template< bool... TBn >
struct BooleanOrByValue< true, TBn... > : public BooleanTrue {
};

template< bool... TBn >
struct BooleanOrByValue< false, TBn... > : public BooleanConstant< BooleanOrByValue< TBn... >::value > {
};

} // namespace BR
