#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

struct IsStaticCastableTest {
	template< typename TFrom, typename TTo, typename = decltype(static_cast<TTo>(make_rvalue<TFrom>())) >
	static BooleanTrue test(int);

	template< typename TFrom, typename TTo >
	static BooleanFalse test(...);
};

template< typename TFrom, typename TTo >
using IsStaticCastable = decltype(IsStaticCastableTest::test< TFrom, TTo >(0));

} // namespace TypeOperate
} // namespace Detail

template< typename TFrom, typename TTo >
struct IsStaticCastable : Boolean< Detail::TypeOperate::IsStaticCastable< TFrom, TTo > > {};

template< typename TFrom, typename TTo >
struct NotStaticCastable : BooleanNot< Detail::TypeOperate::IsStaticCastable< TFrom, TTo > > {};

} // namespace BR