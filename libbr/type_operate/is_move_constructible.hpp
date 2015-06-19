#pragma once
#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/add_rvalue_reference.hpp>
#include <libbr/type_operate/is_constructible.hpp>
#include <libbr/type_operate/is_referenceable.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
using IsMoveConstructible = BooleanAnd<
	IsReferenceable< T >,
	IsConstructible< T, AddRValueReference< T > >
>;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsMoveConstructible : Boolean< Detail::TypeOperate::IsMoveConstructible< T > > {};

template< typename T >
struct NotMoveConstructible : BooleanNot< Detail::TypeOperate::IsMoveConstructible< T > > {};

} // namespace BR