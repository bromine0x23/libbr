#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_arithmetic.hpp>
#include <libbr/type_operate/is_void.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
using IsFundamental = BooleanOr< IsArithmetic< T >, IsVoid< T > >;

} // namespace Detail

template< typename T >
struct IsFundamental : Boolean< Detail::IsFundamental< T > > {};

template< typename T >
struct NotFundamental : BooleanNot< Detail::IsFundamental< T > > {};

} // namespace TypeOperate
} // namespace BR

