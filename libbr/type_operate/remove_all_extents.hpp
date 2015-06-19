#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeRemoveAllExtents : TypeWrapper< T > {};

template< typename T >
struct TypeRemoveAllExtents< T [] > : TypeRemoveAllExtents< T > {};

template< typename T, Size S >
struct TypeRemoveAllExtents< T [S] > : TypeRemoveAllExtents< T > {};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct TypeRemoveAllExtents : TypeRewrap< Detail::TypeOperate::TypeRemoveAllExtents< T > > {};

template< typename T >
using RemoveAllExtents = TypeUnwrap< TypeRemoveAllExtents< T > >;

} // namespace BR



