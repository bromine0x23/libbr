#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename TFrom, typename TTo >
struct TypeMapQualifier : TypeWrapper< TTo > {};

template< typename TFrom, typename TTo >
struct TypeMapQualifier< TFrom &, TTo > : TypeWrapper< TypeUnwrap< TypeMapQualifier< TFrom, TTo > > & > {};

template< typename TFrom, typename TTo >
struct TypeMapQualifier< TFrom &&, TTo > : TypeWrapper< TypeUnwrap< TypeMapQualifier< TFrom, TTo > > && > {};

template< typename TFrom, typename TTo >
struct TypeMapQualifier< TFrom const, TTo > : TypeWrapper< TypeUnwrap< TypeMapQualifier< TFrom, TTo > > const > {};

template< typename TFrom, typename TTo >
struct TypeMapQualifier< TFrom volatile , TTo > : TypeWrapper< TypeUnwrap< TypeMapQualifier< TFrom, TTo > > volatile > {};

template< typename TFrom, typename TTo >
struct TypeMapQualifier< TFrom const volatile , TTo > : TypeWrapper< TypeUnwrap< TypeMapQualifier< TFrom, TTo > > const volatile > {};

} // namespace TypeOperate
} // namespace Detail

template< typename TFrom, typename TTo >
struct TypeMapQualifier : TypeRewrap< Detail::TypeOperate::TypeMapQualifier< TFrom, TTo > > {};

template< typename TFrom, typename TTo >
using MapQualifier = TypeUnwrap< TypeMapQualifier< TFrom, TTo > >;

} // namespace BR
