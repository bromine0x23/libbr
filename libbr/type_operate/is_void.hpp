#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsVoidBasic : BooleanFalse {};

template<>
struct IsVoidBasic< void > : BooleanTrue {};

template< typename T >
struct IsVoid : IsVoidBasic< RemoveConstVolatile< T > > {};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsVoid : Boolean< Detail::TypeOperate::IsVoid< T > > {};

template< typename T >
struct NotVoid : BooleanNot< Detail::TypeOperate::IsVoid< T > > {};

} // namespace BR
