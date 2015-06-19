#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename T >
struct TypeRemoveReference : TypeWrapper< T > {};

template< typename T >
struct TypeRemoveReference< T & > : TypeWrapper< T > {};

template< typename T >
struct TypeRemoveReference< T && > : TypeWrapper< T > {};

template< typename T >
using RemoveReference = TypeUnwrap< TypeRemoveReference< T > >;

} // namespace BR