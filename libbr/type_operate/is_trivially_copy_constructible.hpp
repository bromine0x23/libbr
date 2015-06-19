#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

// TODO: IsTriviallyCopyConstructible
template< typename T >
struct IsTriviallyCopyConstructible {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Not implement yet.");
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsTriviallyCopyConstructible : Boolean< Detail::TypeOperate::IsTriviallyCopyConstructible< T > > {};

template< typename T >
struct NotTriviallyCopyConstructible : BooleanNot< Detail::TypeOperate::IsTriviallyCopyConstructible< T > > {};

} // namespace BR