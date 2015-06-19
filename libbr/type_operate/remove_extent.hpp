#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename T >
struct TypeRemoveExtent : TypeWrapper< T > {};

template< typename T >
struct TypeRemoveExtent< T [] > : TypeWrapper< T > {};

template< typename T, Size S >
struct TypeRemoveExtent< T [S] > : TypeWrapper< T > {};

template< typename T >
using RemoveExtent = TypeUnwrap< TypeRemoveExtent< T > >;

} // namespace BR


