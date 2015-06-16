#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

// TODO
template< typename T >
struct IsTriviallyAssignable {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Not implement yet.");
};

} // namespace Detail

template< typename T >
struct IsTriviallyAssignable : Boolean< Detail::IsTriviallyAssignable< T > > {};

template< typename T >
struct NotTriviallyAssignable : BooleanNot< Detail::IsTriviallyAssignable< T > > {};

} // namespace TypeOperate
} // namespace BR