/**
 * @file
 * @brief MaxIntegerConstant
 * @author Bromine0x23
 * @since 2015/11/7
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/utility/integer_constant.hpp>
#include <libbr/utility/integer_sequence.hpp>

namespace BR {

template< typename ... TIn >
struct TypeMaxInteger;

template< typename TI0>
struct TypeMaxInteger<TI0> : TypeWrapper< TI0 > {
};

template< typename TI0, typename TI1, typename ...TIn >
struct TypeMaxInteger< TI0, TI1, TIn... > : TypeMaxInteger< ConditionalByValue< (TI0::value < TI1::value), TI1, TI0 >, TIn... > {
};

template< typename ... TIn >
using MaxInteger = TypeUnwrap< TypeMaxInteger< TIn... > >;

} // namespace BR