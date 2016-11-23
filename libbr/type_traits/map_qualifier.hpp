/**
 * @file
 * @brief 映射修饰符
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief TypeMapQualifier
 * @tparam TFrom
 * @tparam TTo
 * @see MapQualifier
 */
template< typename TFrom, typename TTo >
struct TypeMapQualifier;

/**
 * @brief MapQualifier
 * @tparam TFrom
 * @tparam TTo
 * @see TypeMapQualifier
 */
template< typename TFrom, typename TTo >
using MapQualifier = TypeUnwrap< TypeMapQualifier< TFrom, TTo > >;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename TFrom, typename TTo >
struct TypeMapQualifier : TypeWrapper< TTo > {};

template< typename TFrom, typename TTo >
struct TypeMapQualifier< TFrom &, TTo > : TypeWrapper< TypeUnwrap< TypeMapQualifier< TFrom, TTo > > & > {};

template< typename TFrom, typename TTo >
struct TypeMapQualifier< TFrom &&, TTo > : TypeWrapper< TypeUnwrap< TypeMapQualifier< TFrom, TTo > > && > {};

template< typename TFrom, typename TTo >
struct TypeMapQualifier< TFrom const, TTo > : TypeWrapper< TypeUnwrap< TypeMapQualifier< TFrom, TTo > > const > {};

template< typename TFrom, typename TTo >
struct TypeMapQualifier< TFrom volatile , TTo > : TypeWrapper< TypeUnwrap< TypeMapQualifier< TFrom, TTo > > volatile > {};

template< typename TFrom, typename TTo >
struct TypeMapQualifier< TFrom const volatile , TTo > : TypeWrapper< TypeUnwrap< TypeMapQualifier< TFrom, TTo > > const volatile > {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename TFrom, typename TTo >
struct TypeMapQualifier : TypeRewrap< Detail::TypeTraits::TypeMapQualifier< TFrom, TTo > > {};

} // namespace TypeTraits


} // namespace BR
