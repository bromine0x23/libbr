#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_HAS_TRIVIAL_MOVE_CONSTRUCTOR)
#  include <libbr/type_operate/is_pod.hpp>
#  include <libbr/type_operate/is_volatile.hpp>
#endif

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_HAS_TRIVIAL_MOVE_CONSTRUCTOR)

template< typename T >
using HasTrivialMoveConstructor = BooleanConstant< BR_TYPE_OPERATE_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) >;

#else

template< typename T >
using HasTrivialMoveConstructor = BooleanAnd< IsPOD< T >, NotVolatile< T > >;

#endif // BR_TYPE_OPERATE_HAS_TRIVIAL_MOVE_CONSTRUCTOR

} // namespace Detail

template< typename T >
struct HasTrivialMoveConstructor : Boolean< Detail::HasTrivialMoveConstructor< T > > {};

template< typename T >
struct NoTrivialMoveConstructor : BooleanNot< Detail::HasTrivialMoveConstructor< T > > {};

} // namespace TypeOperate
} // namespace BR