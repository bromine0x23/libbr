#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename T >
struct TypeRemoveVolatile : TypeWrapper< T > {};

template< typename T >
struct TypeRemoveVolatile< T volatile > : TypeWrapper< T > {};

template< typename T >
using RemoveVolatile = TypeUnwrap< TypeRemoveVolatile< T > >;

} // namespace BR