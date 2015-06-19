#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

// TODO: IsTriviallyCopyAssignable
template< typename T >
struct IsTriviallyCopyAssignable {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Not implement yet.");
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsTriviallyCopyAssignable : Boolean< Detail::TypeOperate::IsTriviallyCopyAssignable< T > > {};

template< typename T >
struct NotTriviallyCopyAssignable : BooleanNot< Detail::TypeOperate::IsTriviallyCopyAssignable< T > > {};

} // namespace BR