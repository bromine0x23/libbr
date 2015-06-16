#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_constructible.hpp>
#include <libbr/type_operate/is_nothrow_default_constructible.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T, typename ... TArguments >
struct IsNothrowConstructibleBasic;

template< typename T >
struct IsNothrowConstructibleBasic< T > : IsNothrowDefaultConstructible< T > {};

template< typename T, typename TArgument >
struct IsNothrowConstructibleBasic< T, TArgument > : BooleanConstant< noexcept(static_cast< T >(make_rvalue< TArgument >())) > {};

template< typename T, typename ... TArguments >
struct IsNothrowConstructibleBasic : BooleanConstant< noexcept(T(make_rvalue< TArguments >() ...)) > {};

template< typename T, typename ... TArguments >
using IsNothrowConstructible = BooleanAnd<
	IsConstructible< T, TArguments ... >,
	IsNothrowConstructibleBasic< T, TArguments ... >
>;

} // namespace Detail

template< typename T, typename ... TArguments >
struct IsNothrowConstructible : Boolean< Detail::IsNothrowConstructible< T, TArguments ... > > {};

template< typename T, typename ... TArguments >
struct NotNothrowConstructible : BooleanNot< Detail::IsNothrowConstructible< T, TArguments ... > > {};

} // namespace TypeOperate
} // namespace BR