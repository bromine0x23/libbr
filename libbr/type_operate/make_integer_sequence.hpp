/**
 * @file
 * @brief MakeIntegerSequence
 * @author Bromine0x23
 * @since 2015/11/1
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/utility/integer_sequence.hpp>

namespace BR {

template< typename TValue, TValue from, TValue to >
struct TypeMakeIntegerSequence;

template< typename TValue, TValue from, TValue to >
using MakeIntegerSequence = TypeUnwrap< TypeMakeIntegerSequence< TValue, from, to > >;

template< Size from, Size to >
using TypeMakeIndexSequence = TypeMakeIntegerSequence< Size, from, to >;

template< Size from, Size to >
using MakeIndexSequence = MakeIntegerSequence< Size, from, to >;

namespace Detail {
namespace TypeOperate {

template< typename TValue, TValue from, TValue to, TValue ... values >
struct TypeMakeIntegerSequence;

template< typename TValue, TValue from, TValue to, TValue ... values >
struct TypeMakeIntegerSequence : public TypeMakeIntegerSequence< TValue, from + 1, to, values ..., from > {
};

template< typename TValue, TValue to, TValue ... values >
struct TypeMakeIntegerSequence< TValue, to, to, values ... > : public TypeWrapper< IntegerSequence< TValue, values ... > > {
};

} // namespace TypeOperate
} // namespace Detail

template< typename TValue, TValue from, TValue to >
struct TypeMakeIntegerSequence : TypeRewrap< Detail::TypeOperate::TypeMakeIntegerSequence< TValue, from, to > > {
};

} // namespace BR