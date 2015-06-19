#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_function.hpp>
#include <libbr/type_operate/is_object.hpp>
#include <libbr/type_operate/is_reference.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsReferenceable = BooleanOr< IsObject< T >, IsReference< T >, IsFunction< T > >;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsReferenceable : Boolean< Detail::TypeOperate::IsReferenceable< T > > {};

template< typename T >
struct NotReferenceable : BooleanNot< Detail::TypeOperate::IsReferenceable< T > > {};

} // namespace BR
