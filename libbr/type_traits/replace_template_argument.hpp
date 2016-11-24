/**
 * @file
 * @brief 替换模版参数
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief TypeReplaceFirstTemplateArgument
 * @tparam T
 * @tparam TNewArg
 * @see ReplaceFirstTemplateArgument
 */
template< typename T, typename TNewArg >
struct TypeReplaceFirstTemplateArgument;

/**
 * @brief ReplaceFirstTemplateArgument
 * @tparam T
 * @tparam TNewArg
 * @see TypeReplaceFirstTemplateArgument
 */
template< typename T, typename TNewArg >
using ReplaceFirstTemplateArgument = TypeUnwrap< TypeReplaceFirstTemplateArgument< T, TNewArg > >;

} // namespace TypeTraits



inline namespace TypeTraits {

template< typename T, typename TNewArg >
struct TypeReplaceFirstTemplateArgument {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >{}, "Type must be template class.");
};

template< template< typename, typename... > class TemplateClass, typename TArg0, typename... TArgs, typename TNewArg >
struct TypeReplaceFirstTemplateArgument< TemplateClass< TArg0, TArgs... >, TNewArg > : TypeWrapper< TemplateClass< TNewArg, TArgs... > >  {};

} // namespace TypeTraits


} // namespace BR
