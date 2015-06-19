#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename T >
struct TypeAddVolatile : TypeWrapper< T volatile > {};

template< typename T >
struct TypeAddVolatile< T &  > : TypeWrapper< T & > {};

template< typename T >
using AddVolatile = TypeUnwrap< TypeAddVolatile< T > >;

} // namespace BR
