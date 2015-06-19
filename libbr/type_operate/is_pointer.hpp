#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_member_pointer.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsPointerBasic : BooleanFalse {};

template< typename T >
struct IsPointerBasic< T * > : BooleanTrue {};

template< typename T >
using IsPointer = BooleanAnd< IsPointerBasic< RemoveConstVolatile< T > >, NotMemberPointer< T > >;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsPointer : Boolean< Detail::TypeOperate::IsPointer< T > > {};

template< typename T >
struct NotPointer : BooleanNot< Detail::TypeOperate::IsPointer< T > > {};

} // namespace BR