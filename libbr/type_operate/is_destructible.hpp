#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_array.hpp>
#include <libbr/type_operate/is_function.hpp>
#include <libbr/type_operate/is_object.hpp>
#include <libbr/type_operate/is_scalar.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/remove_all_extents.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

struct IsDestructibleTester {
	template< typename T, typename = decltype(make_reference< T >().~T()) >
	static BooleanTrue test(T *);

	template< typename T >
	static BooleanFalse test(...);
};

template< typename T >
using IsDestructibleBasic = decltype(IsDestructibleTester::test< T >(nullptr));

template< typename T >
using IsDestructible = BooleanAnd<
	NotVoid< T >,
	NotArrayUnknownBounds< T >,
	NotFunction< T >,
	BooleanOr<
		IsReference< T >,
		IsScalar< T >,
		IsDestructibleBasic< RemoveAllExtents< T > >
	>
>;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsDestructible : Boolean< Detail::TypeOperate::IsDestructible< T > > {};

template< typename T >
struct NotDestructible : BooleanNot< Detail::TypeOperate::IsDestructible< T > > {};

} // namespace BR