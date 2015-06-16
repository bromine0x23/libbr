#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct IsConst : BooleanFalse {};

template< typename T >
struct IsConst< T const > : BooleanTrue {};

} // namespace Detail

template< typename T >
struct IsConst : Boolean< Detail::IsConst< T > > {};

template< typename T >
struct NotConst : BooleanNot< Detail::IsConst< T > > {};

} // namespace TypeOperate
} // namespace BR
