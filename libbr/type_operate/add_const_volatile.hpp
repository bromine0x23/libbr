#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {
namespace TypeOperate {

template< typename T >
struct TypeAddConstVolatile : TypeWrapper< T const volatile > {};

template< typename T >
struct TypeAddConstVolatile< T & > : TypeWrapper< T & > {};

template< typename T >
using AddConstVolatile = TypeUnwrap< TypeAddConstVolatile< T > >;

} // namespace TypeOperate
} // namespace BR
