#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

// TODO
template< typename T >
struct IsTriviallyDefaultConstructible {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Not implement yet.");
};

} // namespace Detail

template< typename T >
struct IsTriviallyDefaultConstructible : Boolean< Detail::IsTriviallyDefaultConstructible< T > > {};

template< typename T >
struct NotTriviallyDefaultConstructible : BooleanNot< Detail::IsTriviallyDefaultConstructible< T > > {};

} // namespace TypeOperate
} // namespace BR