#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T0, typename T1 >
struct IsSame : BooleanFalse {};

template< typename T >
struct IsSame< T, T > : BooleanTrue {};

} // namespace Detail

template< typename T0, typename T1 >
struct IsSame : Boolean< Detail::IsSame< T0, T1 > > {};

template< typename T0, typename T1 >
struct NotSame : BooleanNot< Detail::IsSame< T0, T1 > > {};

} // namespace TypeOperate
} // namespace BR