/**
 * @file
 * @brief MakeIntegerSequence
 * @author Bromine0x23
 * @since 2015/11/1
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/utility/integral_sequence.hpp>

namespace BR {

template< typename TValue, TValue from, TValue to >
struct TypeMakeIntegralSequence;

template< typename TValue, TValue from, TValue to >
using MakeIntegralSequence = TypeUnwrap< TypeMakeIntegralSequence< TValue, from, to > >;

template< Size from, Size to >
using TypeMakeIndexSequence = TypeMakeIntegralSequence< Size, from, to >;

template< Size from, Size to >
using MakeIndexSequence = MakeIntegralSequence< Size, from, to >;

namespace Detail {
namespace TypeOperate {

template< typename TValue, TValue from, TValue to, TValue ... values >
struct TypeMakeIntegralSequence;

template< typename TValue, TValue from, TValue to, TValue ... values >
struct TypeMakeIntegralSequence : public TypeRewrap< TypeMakeIntegralSequence< TValue, from + 1, to, values ..., from > > {
};

template< typename TValue, TValue to, TValue ... values >
struct TypeMakeIntegralSequence< TValue, to, to, values ... > : public TypeWrapper< IntegralSequence< TValue, values ... > > {
};

} // namespace TypeOperate
} // namespace Detail

template< typename TValue, TValue from, TValue to >
struct TypeMakeIntegralSequence : TypeRewrap< Detail::TypeOperate::TypeMakeIntegralSequence< TValue, from, to > > {
};

} // namespace BR