#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

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

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsArrayKnownBounds : Boolean< Detail::TypeOperate::IsArrayKnownBounds< T > > {};

template< typename T >
struct NotArrayKnownBounds : BooleanNot< Detail::TypeOperate::IsArrayKnownBounds< T > > {};

template< typename T >
struct IsArrayUnknownBounds : Boolean< Detail::TypeOperate::IsArrayUnknownBounds< T > > {};

template< typename T >
struct NotArrayUnknownBounds : BooleanNot< Detail::TypeOperate::IsArrayUnknownBounds< T > > {};

template< typename T >
struct IsArray : Boolean< Detail::TypeOperate::IsArray< T > > {};

template< typename T >
struct NotArray : BooleanNot< Detail::TypeOperate::IsArray< T > > {};

} // namespace BR
