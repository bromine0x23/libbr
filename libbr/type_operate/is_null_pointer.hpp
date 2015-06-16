#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct IsNullPointerBasic : BooleanFalse {};

template<>
struct IsNullPointerBasic< NullPointer > : BooleanTrue {};

template< typename T >
struct IsNullPointer : IsNullPointerBasic< RemoveConstVolatile< T > > {};

} // namespace Detail

template< typename T >
struct IsNullPointer : Boolean< Detail::IsNullPointer< T > > {};

template< typename T >
struct NotNullPointer: BooleanNot< Detail::IsNullPointer< T > > {};

} // namespace TypeOperate
} // namespace BR
