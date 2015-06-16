#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {
namespace TypeOperate {

template< typename T >
struct TypeRemoveConstVolatile : TypeWrapper< T > {};

template< typename T >
struct TypeRemoveConstVolatile< T const > : TypeWrapper< T > {};

template< typename T >
struct TypeRemoveConstVolatile< T volatile > : TypeWrapper< T > {};

template< typename T >
struct TypeRemoveConstVolatile< T const volatile > : TypeWrapper< T > {};

template< typename T >
using RemoveConstVolatile = TypeUnwrap< TypeRemoveConstVolatile< T > >;

} // namespace TypeOperate
} // namespace BR