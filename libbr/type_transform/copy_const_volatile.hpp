/**
 * @file
 * @brief 映射 \em cv 修饰符
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief TypeCopyConstVolatile
 * @tparam TTemplate
 * @tparam TParam
 * @see TypeWrapper
 * @see CopyConstVolatile
 */
template< typename TTemplate, typename TParam >
struct TypeCopyConstVolatile;

/**
 * @brief TypeCopyConstVolatile 的简写版本
 * @tparam TTemplate
 * @tparam TParam
 * @see TypeCopyConstVolatile
 */
template< typename TTemplate, typename TParam >
using CopyConstVolatile = TypeUnwrap< TypeCopyConstVolatile< TTemplate, TParam > >;

} // namespace TypeTransform



namespace _::TypeTransform {

template< typename TTemplate, typename TParam >
struct TypeCopyConstVolatile : public TypeWrapper<TParam> {};

template< typename TTemplate, typename TParam >
struct TypeCopyConstVolatile< TTemplate const, TParam > : public TypeWrapper< TParam const > {};

template< typename TTemplate, typename TParam >
struct TypeCopyConstVolatile< TTemplate volatile, TParam > : public TypeWrapper< TParam volatile > {};

template< typename TTemplate, typename TParam >
struct TypeCopyConstVolatile< TTemplate const volatile, TParam > : public TypeWrapper< TParam const volatile > {};

} // namespace _::TypeTransform

inline namespace TypeTransform {

template< typename TTemplate, typename TParam >
struct TypeCopyConstVolatile : public TypeRewrap< _::TypeTransform::TypeCopyConstVolatile< TTemplate, TParam > > {};

} // namespace TypeTransform

} // namespace BR
