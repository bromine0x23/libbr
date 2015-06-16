#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_operate/is_nothrow_assignable.hpp>
#include <libbr/type_operate/is_referenceable.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
using IsNothrowMoveAssignable = BooleanAnd<
	IsReferenceable< T >,
	IsNothrowAssignable< AddLValueReference< T >, AddRValueReference< T > >
>;

} // namespace Detail

template< typename T >
struct IsNothrowMoveAssignable : Boolean< Detail::IsNothrowMoveAssignable< T > > {};

template< typename T >
struct NotNothrowMoveAssignable : BooleanNot< Detail::IsNothrowMoveAssignable< T > > {};

} // namespace TypeOperate
} // namespace BR