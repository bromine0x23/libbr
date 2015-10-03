#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename T >
struct TypeTemplateArguments {
	static_assert(sizeof(T *) != sizeof(nullptr), "Type must be template class.");
};

template< template< typename ... > class TemplateClass, typename... TArgs >
struct TypeTemplateArguments< TemplateClass< TArgs... > > : TypeWrapper< Types< TArgs... > >  {};

template< typename T >
using TemplateArguments = TypeUnwrap< TypeTemplateArguments<T> >;

template< typename T >
struct TypeFirstTemplateArgument {
	static_assert(sizeof(T *) != sizeof(nullptr), "Type must be template class.");
};

template< template< typename, typename... > class TemplateClass, typename TArg0, typename... TArgs >
struct TypeFirstTemplateArgument< TemplateClass< TArg0, TArgs... > > : TypeWrapper< TArg0 >  {};

template< typename T >
using FirstTemplateArgument = TypeUnwrap< TypeFirstTemplateArgument<T> >;

} // namespace BR
