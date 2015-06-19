#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#include <libbr/type_operate/is_pod.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_TRIVIAL_DEFAULT_CONSTRUCTOR)

template< typename T >
using HasTrivialDefaultConstructorBasic = BooleanConstant< BR_HAS_TRIVIAL_DEFAULT_CONSTRUCTOR(T) >;

#else

template< typename T >
using HasTrivialDefaultConstructorBasic = BooleanFalse;

#endif // BR_HAS_TRIVIAL_DEFAULT_CONSTRUCTOR

template< typename T >
using HasTrivialDefaultConstructor = BooleanOr< IsPOD< T >, HasTrivialDefaultConstructorBasic< T > >;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasTrivialDefaultConstructor : Boolean< Detail::TypeOperate::HasTrivialDefaultConstructor< T > > {};

template< typename T >
struct NoTrivialDefaultConstructor : BooleanNot< Detail::TypeOperate::HasTrivialDefaultConstructor< T > > {};

} // namespace BR
