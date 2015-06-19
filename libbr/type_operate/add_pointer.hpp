#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/remove_reference.hpp>

namespace BR {

template< typename T >
struct TypeAddPointer : TypeWrapper< RemoveReference< T > * > {};

template< typename T >
using AddPointer = TypeUnwrap< TypeAddPointer< T > >;

} // namespace BR
