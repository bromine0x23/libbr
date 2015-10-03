#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#include <libbr/type_traits/is_pod.hpp>

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
struct HasTrivialDefaultConstructor : BooleanRewrapPositive< Detail::TypeOperate::HasTrivialDefaultConstructor< T > > {};

template< typename T >
struct NoTrivialDefaultConstructor : BooleanRewrapNegative< Detail::TypeOperate::HasTrivialDefaultConstructor< T > > {};

} // namespace BR
