/**
 * @file
 * @brief 获取类模版实例的首个参数
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_transform/template_arguments.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief TypeTemplateArguments
 * @tparam T
 * @see FirstTemplateArgument
 */
template< typename T >
struct TypeFirstTemplateArgument;

/**
 * @brief FirstTemplateArgument
 * @tparam T
 * @see TypeFirstTemplateArgument
 */
template< typename T >
using FirstTemplateArgument = TypeUnwrap< TypeFirstTemplateArgument<T> >;

} // namespace TypeTransform



namespace _ {
namespace TypeTransform {

template< typename T >
using TypeFirstTemplateArgument = TypeWrapper< typename TemplateArguments<T>::template Get<0> >;

} // namespace TypeTransform
} // namespace _

inline namespace TypeTransform {

template< typename T >
struct TypeFirstTemplateArgument : public TypeRewrap< _::TypeTransform::TypeFirstTemplateArgument<T> > {};

} // namespace TypeTransform

} // namespace BR
