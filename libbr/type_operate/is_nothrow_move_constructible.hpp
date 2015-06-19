#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_operate/is_nothrow_constructible.hpp>
#include <libbr/type_operate/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsNothrowMoveConstructible = BooleanAnd<
	IsReferenceable< T >,
	IsNothrowConstructible< AddRValueReference< T > >
>;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsNothrowMoveConstructible : Boolean< Detail::TypeOperate::IsNothrowMoveConstructible< T > > {};

template< typename T >
struct NotNothrowMoveConstructible : BooleanNot< Detail::TypeOperate::IsNothrowMoveConstructible< T > > {};

} // namespace BR