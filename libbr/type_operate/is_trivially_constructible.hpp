#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

// TODO: IsTriviallyConstructible
template< typename T >
struct IsTriviallyConstructible {
	static_assert(sizeof(T *) == sizeof(nullptr), "Not implement yet.");
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsTriviallyConstructible : Boolean< Detail::TypeOperate::IsTriviallyConstructible< T > > {};

template< typename T >
struct NotTriviallyConstructible : BooleanNot< Detail::TypeOperate::IsTriviallyConstructible< T > > {};

} // namespace BR