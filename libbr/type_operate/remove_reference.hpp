#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {
namespace TypeOperate {

template< typename T >
struct TypeRemoveReference : TypeWrapper< T > {};

template< typename T >
struct TypeRemoveReference< T & > : TypeWrapper< T > {};

template< typename T >
struct TypeRemoveReference< T && > : TypeWrapper< T > {};

template< typename T >
using RemoveReference = TypeUnwrap< TypeRemoveReference< T > >;

} // namespace TypeOperate
} // namespace BR