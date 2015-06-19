#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsConst : BooleanFalse {};

template< typename T >
struct IsConst< T const > : BooleanTrue {};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsConst : Boolean< Detail::TypeOperate::IsConst< T > > {};

template< typename T >
struct NotConst : BooleanNot< Detail::TypeOperate::IsConst< T > > {};

} // namespace BR
