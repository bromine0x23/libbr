#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_assignable.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T, typename TArgument >
struct IsNothrowAssignableBasic : BooleanConstant< noexcept(make_rvalue< T >() = make_rvalue< TArgument >()) > {};

template< typename T, typename TArgument >
using IsNothrowAssignable = BooleanAnd<
	IsAssignable< T, TArgument >,
	IsNothrowAssignableBasic< T, TArgument >
>;

} // namespace TypeOperate
} // namespace Detail

template< typename T, typename TArgument >
struct IsNothrowAssignable : Boolean< Detail::TypeOperate::IsNothrowAssignable< T, TArgument > > {};

template< typename T, typename TArgument >
struct NotNothrowAssignable : BooleanNot< Detail::TypeOperate::IsNothrowAssignable< T, TArgument > > {};

} // namespace BR