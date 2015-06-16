#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_operate/is_assignable.hpp>
#include <libbr/type_operate/is_referenceable.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
using IsMoveAssignable = BooleanAnd<
	IsReferenceable< T >,
	IsAssignable< AddLValueReference< T >, AddRValueReference< T > >
>;

} // namespace Detail

template< typename T >
struct IsMoveAssignable : Boolean< Detail::IsMoveAssignable< T > > {};

template< typename T >
struct NotMoveAssignable : BooleanNot< Detail::IsMoveAssignable< T > > {};

} // namespace TypeOperate
} // namespace BR