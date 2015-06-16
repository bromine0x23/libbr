#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {
namespace TypeOperate {

template< bool condition, typename TWhenTrue, typename TWhenFalse = void >
struct TypeConditionalByValue : TypeWrapper< TWhenTrue > {};

template< typename TWhenTrue, typename TWhenFalse >
struct TypeConditionalByValue< false, TWhenTrue, TWhenFalse > : TypeWrapper< TWhenFalse > {};

template< bool condition, typename TWhenTrue, typename TWhenFalse = void >
using ConditionalByValue = TypeUnwrap< TypeConditionalByValue< condition, TWhenTrue, TWhenFalse > >;

template< typename TCondition, typename TWhenTrue, typename TWhenFalse = void >
struct TypeConditional : TypeWrapper< ConditionalByValue< TCondition::value, TWhenTrue, TWhenFalse > > {};

template< typename TCondition, typename TWhenTrue, typename TWhenFalse = void >
using Conditional = TypeUnwrap< TypeConditional< TCondition, TWhenTrue, TWhenFalse > >;

} // namespace TypeOperate
} // namespace BR