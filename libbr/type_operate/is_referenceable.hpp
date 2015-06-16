#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_function.hpp>
#include <libbr/type_operate/is_object.hpp>
#include <libbr/type_operate/is_reference.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
using IsReferenceable = BooleanOr< IsObject< T >, IsReference< T >, IsFunction< T > >;

} // namespace Detail

template< typename T >
struct IsReferenceable : Boolean< Detail::IsReferenceable< T > > {};

template< typename T >
struct NotReferenceable : BooleanNot< Detail::IsReferenceable< T > > {};

} // namespace TypeOperate
} // namespace BR
