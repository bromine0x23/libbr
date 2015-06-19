#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_HAS_TRIVIAL_MOVE_ASSIGNMENT)
#  include <libbr/type_operate/is_const.hpp>
#  include <libbr/type_operate/is_pod.hpp>
#  include <libbr/type_operate/is_volatile.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_TRIVIAL_MOVE_ASSIGNMENT)

template< typename T >
using HasTrivialMoveAssignment = BooleanConstant< BR_HAS_TRIVIAL_MOVE_ASSIGNMENT(T) >;

#else

template< typename T >
using HasTrivialMoveAssignment = BooleanAnd< IsPOD< T >, NotConst< T >, NotVolatile< T > >;

#endif // BR_HAS_TRIVIAL_MOVE_ASSIGNMENT

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasTrivialMoveAssignment : Boolean< Detail::TypeOperate::HasTrivialMoveAssignment< T > > {};

template< typename T >
struct NoTrivialMoveAssignment : BooleanNot< Detail::TypeOperate::HasTrivialMoveAssignment< T > > {};

} // namespace BR