#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/is_array.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/remove_all_extents.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

struct IsDefaultConstructibleTester {
	template< typename T, typename = decltype(T()) >
	static BooleanTrue test(T *);

	template< typename T >
	static BooleanFalse test(...);
};

template< typename T >
using IsDefaultConstructibleBasic = BooleanAnd<
	NotVoid< T >,
	decltype(IsDefaultConstructibleTester::test< T >(nullptr))
>;

template< typename T >
using IsDefaultConstructible = Conditional<
	IsArray< T >,
	BooleanAnd<
		IsArrayKnownBounds< T >,
		IsDefaultConstructibleBasic< RemoveAllExtents< T > >
	>,
	IsDefaultConstructibleBasic< T >
>;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsDefaultConstructible : Boolean< Detail::TypeOperate::IsDefaultConstructible< T > > {};

template< typename T, typename ... TArguments >
struct NotDefaultConstructible : BooleanNot< Detail::TypeOperate::IsDefaultConstructible< T > > {};

} // namespace BR