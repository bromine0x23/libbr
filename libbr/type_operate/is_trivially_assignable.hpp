#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

// TODO: IsTriviallyAssignable
template< typename T >
struct IsTriviallyAssignable {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Not implement yet.");
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsTriviallyAssignable : Boolean< Detail::TypeOperate::IsTriviallyAssignable< T > > {};

template< typename T >
struct NotTriviallyAssignable : BooleanNot< Detail::TypeOperate::IsTriviallyAssignable< T > > {};

} // namespace BR