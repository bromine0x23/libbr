#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/is_nothrow_constructible.hpp>
#include <libbr/type_operate/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsNothrowCopyConstructible = BooleanAnd<
	IsReferenceable< T >,
	IsNothrowConstructible< T, AddLValueReference< AddConst< T > > >
>;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsNothrowCopyConstructible : Boolean< Detail::TypeOperate::IsNothrowCopyConstructible< T > > {};

template< typename T >
struct NotNothrowCopyConstructible : BooleanNot< Detail::TypeOperate::IsNothrowCopyConstructible< T > > {};

} // namespace BR