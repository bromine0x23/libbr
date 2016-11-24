/**
 * @file
 * @brief MaxIntegerConstant
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/utility/integral_constant.hpp>
#include <libbr/utility/integral_sequence.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief TypeMaxInteger
 * @tparam TIn
 * @see MaxInteger
 */
template< typename ... TIn >
struct TypeMaxInteger;

/**
 * @brief MaxInteger
 * @tparam TIn
 * @see TypeMaxInteger
 */
template< typename ... TIn >
using MaxInteger = TypeUnwrap< TypeMaxInteger< TIn... > >;

} // namespace TypeTraits



inline namespace TypeTraits {

template< typename TI0>
struct TypeMaxInteger<TI0> : TypeWrapper< TI0 > {};

template< typename TI0, typename TI1, typename ...TIn >
struct TypeMaxInteger< TI0, TI1, TIn... > : TypeMaxInteger< ConditionalByValue< (TI0{} < TI1{}), TI1, TI0 >, TIn... > {};

} // namespace TypeTraits


} // namespace BR