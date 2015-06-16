#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {
namespace TypeOperate {

template< typename T >
struct TypeAddLValueReference : TypeWrapper< T & > {};

template<>
struct TypeAddLValueReference< void  > : TypeWrapper< void > {};

template< typename T >
using AddLValueReference = TypeUnwrap< TypeAddLValueReference< T > >;

} // namespace TypeOperate
} // namespace BR