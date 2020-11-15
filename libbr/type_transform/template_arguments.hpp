/**
 * @file
 * @brief 获取类模版实例的参数
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_sequence.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

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

} // namespace TypeTransform



namespace _::TypeTransform {

template< typename T >
struct TypeTemplateArguments {
	static_assert(sizeof(T *) != sizeof(nullptr), "Type must be template class.");
};

template< template< typename ... > class TemplateClass, typename... TArgs >
struct TypeTemplateArguments< TemplateClass< TArgs... > > : TypeWrapper< TypeSequence< TArgs... > >  {};

} // namespace _::TypeTransform

inline namespace TypeTransform {

template< typename T >
struct TypeTemplateArguments : public TypeRewrap< _::TypeTransform::TypeTemplateArguments<T> > {};

} // namespace TypeTransform

} // namespace BR
