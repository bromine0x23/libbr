#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct IsFloatingPointBasic : BooleanFalse {};

template<>
struct IsFloatingPointBasic< float > : BooleanTrue {};

template<>
struct IsFloatingPointBasic< double > : BooleanTrue {};

template<>
struct IsFloatingPointBasic< long double > : BooleanTrue {};

template< typename T >
struct IsFloatingPoint : IsFloatingPointBasic< RemoveConstVolatile< T > > {};

} // namespace Detail

template< typename T >
struct IsFloatingPoint : Boolean< Detail::IsFloatingPoint< T > > {};

template< typename T >
struct NotFloatingPoint : BooleanNot< Detail::IsFloatingPoint< T > > {};

} // namespace TypeOperate
} // namespace BR