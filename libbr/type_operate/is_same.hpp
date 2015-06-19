#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T0, typename T1 >
struct IsSame : BooleanFalse {};

template< typename T >
struct IsSame< T, T > : BooleanTrue {};

} // namespace TypeOperate
} // namespace Detail

template< typename T0, typename T1 >
struct IsSame : Boolean< Detail::TypeOperate::IsSame< T0, T1 > > {};

template< typename T0, typename T1 >
struct NotSame : BooleanNot< Detail::TypeOperate::IsSame< T0, T1 > > {};

} // namespace BR