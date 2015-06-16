#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct IsFinal {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Not implement yet.");
};

} // namespace Detail

template< typename T >
struct IsFinal : Boolean< Detail::IsFinal< T > > {};

template< typename T >
struct NotFinal : BooleanNot< Detail::IsFinal< T > > {};

} // namespace TypeOperate
} // namespace BR