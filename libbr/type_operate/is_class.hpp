#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_IS_CLASS)
#  include <libbr/type_operate/is_union.hpp>
#endif // !BR_TYPE_OPERATE_IS_CLASS

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_IS_CLASS)

template< typename T >
using IsClass = BooleanConstant< BR_TYPE_OPERATE_IS_CLASS(T) >;

#else

struct IsClassTest {
	template< typename TClass >
	static BooleanTrue test(void(TClass::*)(void));

	template< typename T >
	static BooleanFalse test(...);
};

template< typename T >
struct IsClassBasic = decltype(IsClassTest::test< T >(0));

template< typename T >
using IsClass = BooleanAnd< NotUnion< T >, IsClassBasic >;

#endif // BR_TYPE_OPERATE_IS_CLASS

} // namespace Detail

template< typename T >
struct IsClass : Boolean< Detail::IsClass< T > > {};

template< typename T >
struct NotClass : BooleanNot< Detail::IsClass< T > > {};

} // namespace TypeOperate
} // namespace BR