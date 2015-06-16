#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_lvalue_reference.hpp>
#include <libbr/type_operate/is_rvalue_reference.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
using IsReference = BooleanOr< IsLValueReference< T >, IsRValueReference< T > >;

} // namespace Detail

template< typename T >
struct IsReference : Boolean< Detail::IsReference< T > > {};

template< typename T >
struct NotReference : BooleanNot< Detail::IsReference< T > > {};

} // namespace TypeOperate
} // namespace BR
