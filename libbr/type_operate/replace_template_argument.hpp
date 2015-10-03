#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

template< typename T, typename TNewArg >
struct TypeReplaceFirstTemplateArgument {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Type must be template class.");
};

template< template< typename, typename... > class TemplateClass, typename TArg0, typename... TArgs, typename TNewArg >
struct TypeReplaceFirstTemplateArgument<
	TemplateClass< TArg0, TArgs... >, TNewArg
> : TypeWrapper<
	TemplateClass< TNewArg, TArgs... >
>  {};

template< typename T, typename TNewArg >
using ReplaceFirstTemplateArgument = TypeUnwrap< TypeReplaceFirstTemplateArgument< T, TNewArg > >;

} // namespace BR
