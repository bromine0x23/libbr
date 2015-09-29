#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

// TODO: IsTriviallyMoveConstructible
template< typename T >
struct IsTriviallyMoveConstructible {
	static_assert(sizeof(T *) == sizeof(nullptr), "Not implement yet.");
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsTriviallyMoveConstructible : Boolean< Detail::TypeOperate::IsTriviallyMoveConstructible< T > > {};

template< typename T >
struct NotTriviallyMoveConstructible : BooleanNot< Detail::TypeOperate::IsTriviallyMoveConstructible< T > > {};

} // namespace BR