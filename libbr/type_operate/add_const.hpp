#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename T >
struct TypeAddConst : TypeWrapper< T const > {};

template< typename T >
using AddConst = TypeUnwrap< TypeAddConst< T > >;

} // namespace BR
