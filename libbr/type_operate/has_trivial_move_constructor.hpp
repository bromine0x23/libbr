#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_HAS_TRIVIAL_MOVE_CONSTRUCTOR)
#  include <libbr/type_traits/is_pod.hpp>
#  include <libbr/type_traits/is_volatile.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_TRIVIAL_MOVE_CONSTRUCTOR)

template< typename T >
using HasTrivialMoveConstructor = BooleanConstant< BR_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) >;

#else

template< typename T >
using HasTrivialMoveConstructor = BooleanAnd< IsPOD< T >, NotVolatile< T > >;

#endif // BR_HAS_TRIVIAL_MOVE_CONSTRUCTOR

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasTrivialMoveConstructor : BooleanRewrapPositive< Detail::TypeOperate::HasTrivialMoveConstructor< T > > {};

template< typename T >
struct NoTrivialMoveConstructor : BooleanRewrapNegative< Detail::TypeOperate::HasTrivialMoveConstructor< T > > {};

} // namespace BR