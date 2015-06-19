#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_IS_ABSTRACT)
#  include <libbr/type_operate/is_class.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_ABSTRACT)

template< typename T >
using IsAbstract = BooleanConstant< BR_IS_ABSTRACT(T) >;

#else

struct IsAbstractTest {
	template< typename T >
	static BooleanFalse test(T(*)[1]);

	template< typename T >
	static BooleanTrue test(...);
};

template< typename T >
struct IsAbstractBasic : decltype(IsAbstractTest::test< T >(nullptr)) {
	static_assert(sizeof(T) != 0, "Type must be complete.");
};

template< typename T >
using IsAbstract = BooleanAnd< IsClass< T >, IsAbstractBasic< T > >;

#endif // BR_IS_ABSTRACT

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsAbstract : Boolean< Detail::TypeOperate::IsAbstract< T > > {};

template< typename T >
struct NotAbstract : BooleanNot< Detail::TypeOperate::IsAbstract< T > > {};

} // namespace BR