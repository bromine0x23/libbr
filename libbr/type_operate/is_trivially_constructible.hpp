#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

// TODO
template< typename T >
struct IsTriviallyConstructible {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Not implement yet.");
};

} // namespace Detail

template< typename T >
struct IsTriviallyConstructible : Boolean< Detail::IsTriviallyConstructible< T > > {};

template< typename T >
struct NotTriviallyConstructible : BooleanNot< Detail::IsTriviallyConstructible< T > > {};

} // namespace TypeOperate
} // namespace BR