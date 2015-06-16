#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct TypeRemovePointerBasic : TypeWrapper< T > {};

template< typename T >
struct TypeRemovePointerBasic< T * > : TypeWrapper< T > {};

template< typename T >
using TypeRemovePointer = TypeRemovePointerBasic< RemoveConstVolatile< T > >;

} // namespace Detail

template< typename T >
struct TypeRemovePointer : TypeRewrap< Detail::TypeRemovePointer< T > > {};

template< typename T >
using RemovePointer = TypeUnwrap< TypeRemovePointer< T > >;

} // namespace TypeOperate
} // namespace BR

