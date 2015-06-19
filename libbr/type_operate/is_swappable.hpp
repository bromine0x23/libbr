#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/utility/make_value.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

using ::BR::swap;

struct IsSwappableTest {
	template< typename T, typename = decltype(swap(make_reference<T &>(), make_reference<T &>())) >
	static auto test(int) -> BooleanTrue;

	template< typename T >
	static auto test(...) -> BooleanFalse;
};

template< typename T >
using IsSwappable = decltype(IsSwappableTest::test< T >(0));

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsSwappable : Boolean< Detail::TypeOperate::IsSwappable< T > > {};

template< typename T >
struct NotSwappable : BooleanNot< Detail::TypeOperate::IsSwappable< T > > {};

} // namespace BR