#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

// TODO
template< typename T >
struct IsTriviallyMoveConstructible {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Not implement yet.");
};

} // namespace Detail

template< typename T >
struct IsTriviallyMoveConstructible : Boolean< Detail::IsTriviallyMoveConstructible< T > > {};

template< typename T >
struct NotTriviallyMoveConstructible : BooleanNot< Detail::IsTriviallyMoveConstructible< T > > {};

} // namespace TypeOperate
} // namespace BR