#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_operate/is_nothrow_assignable.hpp>
#include <libbr/type_operate/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsNothrowMoveAssignable = BooleanAnd<
	IsReferenceable< T >,
	IsNothrowAssignable< AddLValueReference< T >, AddRValueReference< T > >
>;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsNothrowMoveAssignable : Boolean< Detail::TypeOperate::IsNothrowMoveAssignable< T > > {};

template< typename T >
struct NotNothrowMoveAssignable : BooleanNot< Detail::TypeOperate::IsNothrowMoveAssignable< T > > {};

} // namespace BR