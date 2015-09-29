#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

// TODO: IsTriviallyDefaultConstructible
template< typename T >
struct IsTriviallyDefaultConstructible {
	static_assert(sizeof(T *) == sizeof(nullptr), "Not implement yet.");
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsTriviallyDefaultConstructible : Boolean< Detail::TypeOperate::IsTriviallyDefaultConstructible< T > > {};

template< typename T >
struct NotTriviallyDefaultConstructible : BooleanNot< Detail::TypeOperate::IsTriviallyDefaultConstructible< T > > {};

} // namespace BR