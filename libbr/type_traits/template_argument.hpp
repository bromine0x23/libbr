/**
 * @file
 * @brief 获取模版参数
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>
#include <libbr/utility/types.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief TypeTemplateArguments
 * @tparam T
 * @see TemplateArguments
 */
template< typename T >
struct TypeTemplateArguments;

/**
 * @brief TemplateArguments
 * @tparam T
 * @see TypeTemplateArguments
 */
template< typename T >
using TemplateArguments = TypeUnwrap< TypeTemplateArguments<T> >;

/**
 * @brief TypeTemplateArguments
 * @tparam T
 * @see FirstTemplateArgument
 */
template< typename T >
struct TypeFirstTemplateArgument : public TypeWrapper< typename TemplateArguments<T>::template Get<0> > {};

/**
 * @brief FirstTemplateArgument
 * @tparam T
 * @see TypeFirstTemplateArgument
 */
template< typename T >
using FirstTemplateArgument = TypeUnwrap< TypeFirstTemplateArgument<T> >;

} // namespace TypeTraits



inline namespace TypeTraits {

template< typename T >
struct TypeTemplateArguments {
	static_assert(sizeof(T *) != sizeof(nullptr), "Type must be template class.");
};

template< template< typename ... > class TemplateClass, typename... TArgs >
struct TypeTemplateArguments< TemplateClass< TArgs... > > : TypeWrapper< Types< TArgs... > >  {};

} // namespace TypeTraits

} // namespace BR
