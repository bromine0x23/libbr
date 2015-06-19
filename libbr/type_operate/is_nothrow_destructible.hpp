#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_array.hpp>
#include <libbr/type_operate/is_function.hpp>
#include <libbr/type_operate/is_object.hpp>
#include <libbr/type_operate/is_reference.hpp>
#include <libbr/type_operate/is_scalar.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/remove_all_extents.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

struct IsNothrowDestructibleTest {
	template< typename T >
	static BooleanConstant< noexcept(make_reference< T >().~T()) > test(T *);

	template< typename T >
	static BooleanFalse test(...);
};

template< typename T >
using IsNothrowDestructibleBasic = decltype(IsNothrowDestructibleTest::test< T >(nullptr));

template< typename T >
using IsNothrowDestructible = BooleanAnd<
	NotVoid< T >,
	NotArrayUnknownBounds< T >,
	NotFunction< T >,
	BooleanOr<
		IsReference< T >,
		IsScalar< T >,
		IsNothrowDestructibleBasic< T >
	>
>;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsNothrowDestructible : Boolean< Detail::TypeOperate::IsNothrowDestructible< T > > {};

template< typename T >
struct NotNothrowDestructible : BooleanNot< Detail::TypeOperate::IsNothrowDestructible< T > > {};

} // namespace BR