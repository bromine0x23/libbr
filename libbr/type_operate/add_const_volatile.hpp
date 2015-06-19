#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename T >
struct TypeAddConstVolatile : TypeWrapper< T const volatile > {};

template< typename T >
using AddConstVolatile = TypeUnwrap< TypeAddConstVolatile< T > >;

} // namespace BR
