#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

// TODO
template< typename T >
struct IsTriviallyCopyAssignable {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Not implement yet.");
};

} // namespace Detail

template< typename T >
struct IsTriviallyCopyAssignable : Boolean< Detail::IsTriviallyCopyAssignable< T > > {};

template< typename T >
struct NotTriviallyCopyAssignable : BooleanNot< Detail::IsTriviallyCopyAssignable< T > > {};

} // namespace TypeOperate
} // namespace BR