#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/types.hpp>

namespace BR {

template< typename T >
struct TypeTemplateArguments {
	static_assert(sizeof(T *) != sizeof(nullptr), "Type must be template class.");
};

template< template< typename ... > class TemplateClass, typename... TArgs >
struct TypeTemplateArguments< TemplateClass< TArgs... > > : TypeWrapper< Types< TArgs... > >  {
};

template< typename T >
using TemplateArguments = TypeUnwrap< TypeTemplateArguments<T> >;

template< typename T >
struct TypeFirstTemplateArgument : TypeWrapper< typename TemplateArguments<T>::template Get<0> > {
};

template< typename T >
using FirstTemplateArgument = TypeUnwrap< TypeFirstTemplateArgument<T> >;

} // namespace BR
