/**
 * @file
 * @brief 替换类模版实例的首个参数
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conditional.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief TypeReplaceFirstTemplateArgument
 * @tparam T
 * @tparam TNewArg
 * @see ReplaceFirstTemplateArgument
 */
template<typename T, typename TNewArg>
struct TypeReplaceFirstTemplateArgument;

/**
 * @brief ReplaceFirstTemplateArgument
 * @tparam T
 * @tparam TNewArg
 * @see TypeReplaceFirstTemplateArgument
 */
template<typename T, typename TNewArg>
using ReplaceFirstTemplateArgument = TypeUnwrap<TypeReplaceFirstTemplateArgument<T, TNewArg>>;

} // namespace TypeTransform



namespace _ {
namespace TypeTransform {

template<typename T, typename TNewArg>
struct TypeReplaceFirstTemplateArgument {
	static_assert(Conditional< BooleanFalse, T, BooleanFalse >{}, "Type must be template class.");
};

template<template<typename, typename...> class TemplateClass, typename TArg0, typename... TArgs, typename TNewArg>
struct TypeReplaceFirstTemplateArgument<TemplateClass<TArg0, TArgs...>, TNewArg> : TypeWrapper<TemplateClass<TNewArg, TArgs...>> {};

} // namespace TypeTransform
} // namespace _

inline namespace TypeTransform {

template<typename T, typename TNewArg>
struct TypeReplaceFirstTemplateArgument : public TypeRewrap< _::TypeTransform::TypeReplaceFirstTemplateArgument<T, TNewArg> > {};

} // namespace TypeTransform

} // namespace BR
