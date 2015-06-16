#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_IS_CONSTRUCTIBLE)
#  include <libbr/type_operate/is_base_of.hpp>
#  include <libbr/type_operate/is_default_constructible.hpp>
#  include <libbr/type_operate/is_destructible.hpp>
#  include <libbr/type_operate/is_static_castable.hpp>
#  include <libbr/type_operate/is_lvalue_reference.hpp>
#  include <libbr/type_operate/is_reference.hpp>
#  include <libbr/type_operate/is_rvalue_reference.hpp>
#  include <libbr/type_operate/is_same.hpp>
#  include <libbr/type_operate/remove_reference.hpp>
#  include <libbr/utility/make_value.hpp>
#endif

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_IS_CONSTRUCTIBLE)

template< typename T, typename ... TArguments >
using IsConstructible = BooleanConstant< BR_TYPE_OPERATE_IS_CONSTRUCTIBLE(T, TArguments ...) >;

#else

template< typename T, typename TArgument >
using IsConstructibleOneBaseToDerivedReference = BooleanAnd<
	NotSame< T, TArgument >,
	IsBaseOf< TArgument, T >
>;

template< typename T, typename TArgument >
using IsConstructibleOneLValueToRValueReference = BooleanAnd<
	NotFunction< TArgument >,
	BooleanOr<
		NotSame< T, TArgument >,
		IsBaseOf< TArgument, T >
	>
>;

template< typename T, typename TArgument >
using IsConstructibleReferenceCast = BooleanAnd<
	IsStaticCastable< TArgument, T >,
	BooleanNot<
		BooleanOr<
			IsConstructibleOneBaseToDerivedReference< RemoveReference< T >, RemoveReference< TArgument > >,
			BooleanAnd<
				IsRValueReference< T >,
				IsLValueReference< TArgument >,
				IsConstructibleOneLValueToRValueReference< RemoveReference< T >, RemoveReference< TArgument > >
			>
		>
	>
>;

struct IsConstructibleOneTest {
	template< typename T, typename TArgument, typename = decltype(::new T(make_rvalue< TArgument >())) >
	static BooleanTrue test(int);

	template< typename T, typename TArgument >
	static BooleanFalse test(...);
};

template< typename T, typename TArgument >
using IsConstructibleOneBasic = decltype(IsConstructibleOneTest::test< T, TArgument >(0));

template< typename T, typename TArgument >
using IsConstructibleOne = Conditional<
	IsReference< T >,
	IsConstructibleReferenceCast< T, TArgument >,
	BooleanAnd<
		IsDestructible< T >,
		IsConstructibleOneBasic< T, TArgument >
	>
>;

struct IsConstructibleManyTest {
	template< typename T, typename ... TArguments, typename = decltype(T(make_rvalue< TArguments >()...)) >
	static BooleanTrue test(int);

	template< typename T, typename TArgument >
	static BooleanFalse test(...);
};

template< typename T, typename ... TArgument >
using IsConstructibleMany = decltype(IsConstructibleManyTest::test< T, TArgument ... >(0));

template< typename T, typename ... TArguments >
struct IsConstructible;

template< typename T >
struct IsConstructible< T > : IsDefaultConstructible< T > {};

template< typename T, typename TArgument >
struct IsConstructible< T, TArgument > : IsConstructibleOne< T, TArgument > {};

template< typename T, typename ... TArguments >
struct IsConstructible : IsConstructibleMany< T, TArguments ... > {
	static_assert(sizeof...(TArguments) > 1, "Only useful for > 1 arguments");
};

#endif // BR_TYPE_OPERATE_IS_CONSTRUCTIBLE

} // namespace Detail

template< typename T, typename ... TArguments >
struct IsConstructible : Boolean< Detail::IsConstructible< T, TArguments ... > > {};

template< typename T, typename ... TArguments >
struct NotConstructible : BooleanNot< Detail::IsConstructible< T, TArguments ... > > {};

} // namespace TypeOperate
} // namespace BR