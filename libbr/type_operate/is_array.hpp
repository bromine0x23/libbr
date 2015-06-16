#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct IsArrayKnownBounds : BooleanFalse {};

template< typename T, Size S >
struct IsArrayKnownBounds< T [S] > : BooleanTrue {};

template< typename T >
struct IsArrayUnknownBounds : BooleanFalse {};

template< typename T >
struct IsArrayUnknownBounds< T [] > : BooleanTrue {};

template< typename T >
using IsArray = BooleanOr< IsArrayKnownBounds< T >, IsArrayUnknownBounds< T > >;

} // namespace Detail

template< typename T >
struct IsArrayKnownBounds : Boolean< Detail::IsArrayKnownBounds< T > > {};

template< typename T >
struct NotArrayKnownBounds : BooleanNot< Detail::IsArrayKnownBounds< T > > {};

template< typename T >
struct IsArrayUnknownBounds : Boolean< Detail::IsArrayUnknownBounds< T > > {};

template< typename T >
struct NotArrayUnknownBounds : BooleanNot< Detail::IsArrayUnknownBounds< T > > {};

template< typename T >
struct IsArray : Boolean< Detail::IsArray< T > > {};

template< typename T >
struct NotArray : BooleanNot< Detail::IsArray< T > > {};

} // namespace TypeOperate
} // namespace BR
