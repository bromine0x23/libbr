#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsLValueReference : BooleanFalse {};

template< typename T >
struct IsLValueReference< T & > : BooleanTrue {};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsLValueReference : Boolean< Detail::TypeOperate::IsLValueReference< T > > {};

template< typename T >
struct NotLValueReference : BooleanNot< Detail::TypeOperate::IsLValueReference< T > > {};

} // namespace BR