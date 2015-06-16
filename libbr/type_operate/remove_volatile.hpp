#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {
namespace TypeOperate {

template< typename T >
struct TypeRemoveVolatile : TypeWrapper< T > {};

template< typename T >
struct TypeRemoveVolatile< T volatile > : TypeWrapper< T > {};

template< typename T >
using RemoveVolatile = TypeUnwrap< TypeRemoveVolatile< T > >;

} // namespace TypeOperate
} // namespace BR