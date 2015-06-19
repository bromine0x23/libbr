#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/is_array.hpp>
#include <libbr/type_operate/is_default_constructible.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/remove_all_extents.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsNothrowDefaultConstructibleBasic : BooleanConstant< noexcept(T()) > {};

template< typename T >
using IsNothrowDefaultConstructible = BooleanAnd<
	IsDefaultConstructible< T >,
	Conditional<
		IsArray< T >,
		BooleanAnd<
			IsArrayKnownBounds< T >,
			IsNothrowDefaultConstructibleBasic< RemoveAllExtents< T > >
		>,
		IsNothrowDefaultConstructibleBasic< T >
	>
>;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsNothrowDefaultConstructible : Boolean< Detail::TypeOperate::IsNothrowDefaultConstructible< T > > {};

template< typename T >
struct NotNothrowDefaultConstructible : BooleanNot< Detail::TypeOperate::IsNothrowDefaultConstructible< T > > {};

} // namespace BR