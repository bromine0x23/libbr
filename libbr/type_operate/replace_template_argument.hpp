#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {
namespace TypeOperate {

template< typename T, typename TArgument >
struct TypeReplaceFirstTemplateArgument {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >::value, "Type must be template class.");
};

template< template< typename, typename... > class TemplateClass, typename TFirstArgument, typename... TOtherArguments, typename TArgument >
struct TypeReplaceFirstTemplateArgument<
	TemplateClass< TFirstArgument, TOtherArguments ... >, TArgument
> : TypeWrapper<
	TemplateClass< TArgument, TOtherArguments ... >
>  {};

template< typename T, typename TArgument >
using ReplaceFirstTemplateArgument = TypeUnwrap< TypeReplaceFirstTemplateArgument< T, TArgument > >;

} // namespace TypeOperate
} // namespace BR
