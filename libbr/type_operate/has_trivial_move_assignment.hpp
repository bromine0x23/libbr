#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_HAS_TRIVIAL_MOVE_ASSIGNMENT)
#  include <libbr/type_operate/is_const.hpp>
#  include <libbr/type_operate/is_pod.hpp>
#  include <libbr/type_operate/is_volatile.hpp>
#endif

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_HAS_TRIVIAL_MOVE_ASSIGNMENT)

template< typename T >
using HasTrivialMoveAssignment = BooleanConstant< BR_TYPE_OPERATE_HAS_TRIVIAL_MOVE_ASSIGNMENT(T) >;

#else

template< typename T >
using HasTrivialMoveAssignment = BooleanAnd< IsPOD< T >, NotConst< T >, NotVolatile< T > >;

#endif // BR_TYPE_OPERATE_HAS_TRIVIAL_MOVE_ASSIGNMENT

} // namespace Detail

template< typename T >
struct HasTrivialMoveAssignment : Boolean< Detail::HasTrivialMoveAssignment< T > > {};

template< typename T >
struct NoTrivialMoveAssignment : BooleanNot< Detail::HasTrivialMoveAssignment< T > > {};

} // namespace TypeOperate
} // namespace BR