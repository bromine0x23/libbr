#pragma once
#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/is_assignable.hpp>
#include <libbr/type_operate/is_referenceable.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
using IsCopyAssignable = BooleanAnd<
	IsReferenceable< T >,
	IsAssignable< AddLValueReference< T >, AddLValueReference< AddConst< T > > >
>;

} // namespace Detail

template< typename T >
struct IsCopyAssignable : Boolean< Detail::IsCopyAssignable< T > > {};

template< typename T >
struct NotCopyAssignable : BooleanNot< Detail::IsCopyAssignable< T > > {};

} // namespace TypeOperate
} // namespace BR