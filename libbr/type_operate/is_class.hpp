#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_IS_CLASS)
#  include <libbr/type_operate/is_union.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_CLASS)

template< typename T >
using IsClass = BooleanConstant< BR_IS_CLASS(T) >;

#else

struct IsClassTest {
	template< typename TClass >
	static BooleanTrue test(void(TClass::*)(void));

	template< typename T >
	static BooleanFalse test(...);
};

template< typename T >
using IsClassBasic = decltype(IsClassTest::test< T >(0));

template< typename T >
using IsClass = BooleanAnd< NotUnion< T >, IsClassBasic<T> >;

#endif // BR_IS_CLASS

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsClass : Boolean< Detail::TypeOperate::IsClass< T > > {};

template< typename T >
struct NotClass : BooleanNot< Detail::TypeOperate::IsClass< T > > {};

} // namespace BR