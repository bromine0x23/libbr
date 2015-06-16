#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_integer.hpp>
#include <libbr/type_operate/is_floating_point.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
using IsArithmetic = BooleanOr< IsInteger< T >, IsFloatingPoint< T > >;

} // namespace Detail

template< typename T >
struct IsArithmetic : Boolean< Detail::IsArithmetic< T > > {};

template< typename T >
struct NotArithmetic : BooleanNot< Detail::IsArithmetic< T > > {};

} // namespace TypeOperate
} // namespace BR

