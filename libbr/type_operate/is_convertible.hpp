#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_IS_CONVERTIBLE)
#  include <libbr/type_operate/is_array.hpp>
#  include <libbr/type_operate/is_function.hpp>
#  include <libbr/type_operate/is_void.hpp>
#  include <libbr/utility/make_value.hpp>
#  include <libbr/utility/yes_no.hpp>
#endif // !BR_TYPE_OPERATE_IS_CONVERTIBLE

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_IS_CONVERTIBLE)

template< typename TFrom, typename TTo >
using IsConvertible = BoolConstant< BR_TYPE_OPERATE_IS_CONVERTIBLE(TFrom, TTo) >;

#else // !defined(BR_TT_IS_CONVERTIBLE)

struct IsConvertibleTest {
	template< typename T >
	static void test_aux(T);

	template< typename TFrom, typename TTo >
	static decltype(test_aux< TTo >(make_rvalue< TFrom >()), BooleanTrue()) test(int);

	template< typename TFrom, typename TTo >
	static BooleanFalse test(...);
};

template< typename TFrom, typename TTo >
using IsConvertibleBasic = decltype(IsConvertibleTest::test< TFrom, TTo >(0));

template< typename TFrom, typename TTo >
using IsConvertible = BooleanAnd<
	NotArray< TTo >,
	NotFunction< TTo >,
	BooleanOr<
		IsVoid< TTo >,
		BooleanAnd<
			NotVoid< TFrom >,
			IsConvertibleBasic< TFrom, TTo >
		>
	>
>;

#endif // BR_TYPE_OPERATE_IS_CONVERTIBLE

} // namespace Detail

template< typename TFrom, typename TTo >
struct IsConvertible : Boolean< Detail::IsConvertible< TFrom, TTo > > {};

template< typename TFrom, typename TTo >
struct NotConvertible : BooleanNot< Detail::IsConvertible< TFrom, TTo > > {};

} // namespace TypeOperate
} // namespace BR
