#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_integer.hpp>
#include <libbr/type_operate/is_floating_point.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsArithmetic = BooleanOr< IsInteger< T >, IsFloatingPoint< T > >;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsArithmetic : Boolean< Detail::TypeOperate::IsArithmetic< T > > {};

template< typename T >
struct NotArithmetic : BooleanNot< Detail::TypeOperate::IsArithmetic< T > > {};

} // namespace BR

