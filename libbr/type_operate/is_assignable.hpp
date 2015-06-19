#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

struct IsAssignableTest {
	template< typename T, typename TArgument, typename = decltype(make_rvalue< T >() = make_rvalue< TArgument >()) >
	static BooleanTrue test(int);

	template< typename T, typename TArgument >
	static BooleanFalse test(...);
};

template< typename T, typename TArgument >
using IsAssignable = decltype(IsAssignableTest::test< T, TArgument >(0));

} // namespace TypeOperate
} // namespace Detail

template< typename T, typename TArgument >
struct IsAssignable : Boolean< Detail::TypeOperate::IsAssignable< T, TArgument > > {};

template< typename T, typename TArgument >
struct NotAssignable : BooleanNot< Detail::TypeOperate::IsAssignable< T, TArgument > > {};

} // namespace BR