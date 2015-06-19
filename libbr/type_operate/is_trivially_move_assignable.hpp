#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

// TODO: IsTriviallyMoveAssignable
template< typename T >
struct IsTriviallyMoveAssignable {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Not implement yet.");
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsTriviallyMoveAssignable : Boolean< Detail::TypeOperate::IsTriviallyMoveAssignable< T > > {};

template< typename T >
struct NotTriviallyMoveAssignable : BooleanNot< Detail::TypeOperate::IsTriviallyMoveAssignable< T > > {};

} // namespace BR