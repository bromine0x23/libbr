#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

// TODO
template< typename T >
struct IsTriviallyMoveAssignable {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Not implement yet.");
};

} // namespace Detail

template< typename T >
struct IsTriviallyMoveAssignable : Boolean< Detail::IsTriviallyMoveAssignable< T > > {};

template< typename T >
struct NotTriviallyMoveAssignable : BooleanNot< Detail::IsTriviallyMoveAssignable< T > > {};

} // namespace TypeOperate
} // namespace BR