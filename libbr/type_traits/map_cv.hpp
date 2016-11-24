/**
 * @file
 * @brief 映射 \em cv 修饰符
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief TypeMapCV
 * @tparam TTemplate
 * @tparam TParam
 * @see MapCV
 */
template< typename TTemplate, typename TParam >
struct TypeMapCV;

/**
 * @brief TypeMapCV 的简写版本
 * @tparam TTemplate
 * @tparam TParam
 * @see TypeMapCV
 */
template< typename TTemplate, typename TParam >
using MapCV = TypeUnwrap< TypeMapCV< TTemplate, TParam > >;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename TTemplate, typename TParam >
struct TypeMapCV : public TypeWrapper<TParam> {};

template< typename TTemplate, typename TParam >
struct TypeMapCV< TTemplate const, TParam > : public TypeWrapper< TParam const > {};

template< typename TTemplate, typename TParam >
struct TypeMapCV< TTemplate volatile, TParam > : public TypeWrapper< TParam volatile > {};

template< typename TTemplate, typename TParam >
struct TypeMapCV< TTemplate const volatile, TParam > : public TypeWrapper< TParam const volatile > {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename TTemplate, typename TParam >
struct TypeMapCV : public TypeRewrap< Detail::TypeTraits::TypeMapCV< TTemplate, TParam > > {};

} // namespace TypeTraits

} // namespace BR
