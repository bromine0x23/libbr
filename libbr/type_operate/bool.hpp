#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/utility/integer_constant.hpp>

namespace BR {

template< typename B >
using Boolean = BooleanConstant< B::value >;

template< typename B >
using BooleanNot = BooleanConstant< !B::value >;

template< typename ... >
struct BooleanAnd;

template<>
struct BooleanAnd<> : BooleanTrue {};

template< typename B0 >
struct BooleanAnd< B0 > : BooleanConstant< B0::value > {};

template< typename B0, typename B1, typename ... Bn >
struct BooleanAnd< B0, B1, Bn ... > : Conditional< B0, BooleanAnd< B1, Bn ... >, B0 > {};

template< typename ... >
struct BooleanOr;

template<>
struct BooleanOr<> : BooleanFalse {};

template< typename B0 >
struct BooleanOr< B0 > : BooleanConstant< B0::value > {};

template< typename B0, typename B1, typename ... Bn >
struct BooleanOr< B0, B1, Bn ... > : Conditional< B0, B0, BooleanOr< B1, Bn ... > > {};

template< bool ... Bn >
using Booleans = Integers< bool, Bn ... >;

template< bool ... >
struct BooleanAndByValue;

template<>
struct BooleanAndByValue<> : BooleanTrue {};

template< bool ... Bn >
struct BooleanAndByValue< true, Bn ... > : BooleanConstant< BooleanAndByValue< Bn ... >::value > {};

template< bool ... Bn >
struct BooleanAndByValue< false, Bn ... > : BooleanFalse {};

template< bool ... >
struct BooleanOrByValue;

template<>
struct BooleanOrByValue<> : BooleanFalse {};

template< bool ... Bn >
struct BooleanOrByValue< false, Bn ... > : BooleanConstant< BooleanOrByValue< Bn ... >::value > {};

template< bool ... Bn >
struct BooleanOrByValue< true, Bn ... > : BooleanTrue{};

} // namespace BR
