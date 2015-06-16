#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {
namespace TypeOperate {

template< typename T >
struct TypeTemplateArguments {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Type must be template class.");
};

template< template< typename ... > class TemplateClass, typename ... TArguments >
struct TypeTemplateArguments< TemplateClass< TArguments ... > > : TypeWrapper< Types< TArguments ... > >  {};

template< typename T >
using TemplateArguments = TypeUnwrap< TypeTemplateArguments< T > >;

template< typename T >
struct TypeFirstTemplateArgument {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Type must be template class.");
};

template< template< typename, typename... > class TemplateClass, typename TFirstArgument, typename... TOtherArguments >
struct TypeFirstTemplateArgument< TemplateClass< TFirstArgument, TOtherArguments ... > > : TypeWrapper< TFirstArgument >  {};

template< typename T >
using FirstTemplateArgument = TypeUnwrap< TypeFirstTemplateArgument< T > >;

} // namespace TypeOperate
} // namespace BR
