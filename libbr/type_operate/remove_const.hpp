#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename T >
struct TypeRemoveConst : TypeWrapper< T > {};

template< typename T >
struct TypeRemoveConst< T const > : TypeWrapper< T > {};

template< typename T >
using RemoveConst = TypeUnwrap< TypeRemoveConst< T > >;

} // namespace BR
