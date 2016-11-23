/**
 * @file
 * @brief MakeIntegerSequence
 * @author Bromine0x23
 * @since 2015/11/1
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integral_sequence.hpp>
#include <libbr/utility/type.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief TypeMakeIntegralSequence
 * @tparam TValue
 * @tparam from
 * @tparam to
 * @see MakeIntegralSequence
 */
template< typename TValue, TValue from, TValue to >
struct TypeMakeIntegralSequence;

/**
 * @brief MakeIntegralSequence
 * @tparam TValue
 * @tparam from
 * @tparam to
 * @see TypeMakeIntegralSequence
 */
template< typename TValue, TValue from, TValue to >
using MakeIntegralSequence = TypeUnwrap< TypeMakeIntegralSequence< TValue, from, to > >;

/**
 * @brief TypeMakeIndexSequence
 * @tparam from
 * @tparam to
 * @see MakeIndexSequence
 */
template< Size from, Size to >
using TypeMakeIndexSequence = TypeMakeIntegralSequence< Size, from, to >;

/**
 * @brief TypeMakeIndexSequence
 * @tparam from
 * @tparam to
 * @see TypeMakeIndexSequence
 */
template< Size from, Size to >
using MakeIndexSequence = MakeIntegralSequence< Size, from, to >;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename TValue, TValue from, TValue to, TValue ... values >
struct TypeMakeIntegralSequence;

template< typename TValue, TValue from, TValue to, TValue ... values >
struct TypeMakeIntegralSequence : public TypeRewrap< TypeMakeIntegralSequence< TValue, from + 1, to, values ..., from > > {};

template< typename TValue, TValue to, TValue ... values >
struct TypeMakeIntegralSequence< TValue, to, to, values ... > : public TypeWrapper< IntegralSequence< TValue, values ... > > {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename TValue, TValue from, TValue to >
struct TypeMakeIntegralSequence : TypeRewrap< Detail::TypeTraits::TypeMakeIntegralSequence< TValue, from, to > > {};

} // namespace TypeTraits

} // namespace BR