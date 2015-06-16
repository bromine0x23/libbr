#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/is_nothrow_assignable.hpp>
#include <libbr/type_operate/is_referenceable.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
using IsNothrowCopyAssignable = BooleanAnd<
	IsReferenceable< T >,
	IsNothrowAssignable< AddLValueReference< T >, AddLValueReference< AddConst< T > > >
>;

} // namespace Detail

template< typename T >
struct IsNothrowCopyAssignable : Boolean< Detail::IsNothrowCopyAssignable< T > > {};

template< typename T >
struct NotNothrowCopyAssignable : BooleanNot< Detail::IsNothrowCopyAssignable< T > > {};

} // namespace TypeOperate
} // namespace BR