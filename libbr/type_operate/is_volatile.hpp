#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsVolatile : BooleanFalse {};

template< typename T >
struct IsVolatile< T volatile > : BooleanTrue{};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsVolatile : Boolean< Detail::TypeOperate::IsVolatile< T > > {};

template< typename T >
struct NotVolatile : BooleanNot< Detail::TypeOperate::IsVolatile< T > > {};

} // namespace BR