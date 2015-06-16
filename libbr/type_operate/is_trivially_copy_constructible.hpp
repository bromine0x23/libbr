#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

// TODO
template< typename T >
struct IsTriviallyCopyConstructible {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Not implement yet.");
};

} // namespace Detail

template< typename T >
struct IsTriviallyCopyConstructible : Boolean< Detail::IsTriviallyCopyConstructible< T > > {};

template< typename T >
struct NotTriviallyCopyConstructible : BooleanNot< Detail::IsTriviallyCopyConstructible< T > > {};

} // namespace TypeOperate
} // namespace BR