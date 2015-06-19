#pragma once
#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_lvalue_reference.hpp>
#include <libbr/type_operate/is_constructible.hpp>
#include <libbr/type_operate/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsCopyConstructible = BooleanAnd<
	IsReferenceable< T >,
	IsConstructible< T, AddLValueReference< AddConst< T > > >
>;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsCopyConstructible : Boolean< Detail::TypeOperate::IsCopyConstructible< T > > {};

template< typename T >
struct NotCopyConstructible : BooleanNot< Detail::TypeOperate::IsCopyConstructible< T > > {};

} // namespace BR