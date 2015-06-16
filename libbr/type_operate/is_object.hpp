#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_function.hpp>
#include <libbr/type_operate/is_reference.hpp>
#include <libbr/type_operate/is_void.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
using IsObject = BooleanAnd< NotReference< T >, NotVoid< T >, NotFunction< T > >;

} // namespace Detail

template< typename T >
struct IsObject : Boolean< Detail::IsObject< T > > {};

template< typename T >
struct NotObject : BooleanNot< Detail::IsObject< T > > {};

} // namespace TypeOperate
} // namespace BR

