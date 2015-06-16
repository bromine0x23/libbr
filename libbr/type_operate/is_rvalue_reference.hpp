#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct IsRValueReference : BooleanFalse {};

template< typename T >
struct IsRValueReference< T && > : BooleanTrue {};

} // namespace Detail

template< typename T >
struct IsRValueReference : Boolean< Detail::IsRValueReference< T > > {};

template< typename T >
struct NotRValueReference : BooleanNot< Detail::IsRValueReference< T > > {};

} // namespace TypeOperate
} // namespace BR