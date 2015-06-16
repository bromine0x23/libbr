#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct IsVoidBasic : BooleanFalse {};

template<>
struct IsVoidBasic< void > : BooleanTrue {};

template< typename T >
struct IsVoid : IsVoidBasic< RemoveConstVolatile< T > > {};

} // namespace Detail

template< typename T >
struct IsVoid : Boolean< Detail::IsVoid< T > > {};

template< typename T >
struct NotVoid : BooleanNot< Detail::IsVoid< T > > {};

} // namespace TypeOperate
} // namespace BR
