#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {
namespace TypeOperate {

template< typename T >
struct TypeAddConst : TypeWrapper< T const > {};

template< typename T >
struct TypeAddConst< T &  > : TypeWrapper< T & > {};

template< typename T >
using AddConst = TypeUnwrap< TypeAddConst< T > >;

} // namespace TypeOperate
} // namespace BR
