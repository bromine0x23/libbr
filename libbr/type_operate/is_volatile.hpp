#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct IsVolatile : BooleanFalse {};

template< typename T >
struct IsVolatile< T volatile > : BooleanTrue{};

} // namespace Detail

template< typename T >
struct IsVolatile : Boolean< Detail::IsVolatile< T > > {};

template< typename T >
struct NotVolatile : BooleanNot< Detail::IsVolatile< T > > {};

} // namespace TypeOperate
} // namespace BR