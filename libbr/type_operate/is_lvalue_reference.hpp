#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct IsLValueReference : BooleanFalse {};

template< typename T >
struct IsLValueReference< T & > : BooleanTrue {};

} // namespace Detail

template< typename T >
struct IsLValueReference : Boolean< Detail::IsLValueReference< T > > {};

template< typename T >
struct NotLValueReference : BooleanNot< Detail::IsLValueReference< T > > {};

} // namespace TypeOperate
} // namespace BR