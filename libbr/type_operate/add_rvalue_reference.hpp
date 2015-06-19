#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename T >
struct TypeAddRValueReference : TypeWrapper< T && > {};

template<>
struct TypeAddRValueReference< void  > : TypeWrapper< void > {};

template< typename T >
using AddRValueReference = TypeUnwrap< TypeAddRValueReference< T > >;

} // namespace BR