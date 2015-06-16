#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_HAS_NOTHROW_MOVE_ASSIGNMENT)
#  include <libbr/type_operate/has_trivial_move_assignment.hpp>
#endif

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_HAS_NOTHROW_MOVE_ASSIGNMENT)

template< typename T >
using HasNothrowMoveAssignment = BooleanConstant< BR_TYPE_OPERATE_HAS_NOTHROW_MOVE_ASSIGNMENT(T) >;

#else

template< typename T >
using HasNothrowMoveAssignment = HasTrivialMoveAssignment< T >;

#endif // BR_TYPE_OPERATE_HAS_TRIVIAL_MOVE_ASSIGNMENT

} // namespace Detail

template< typename T >
struct HasNothrowMoveAssignment : Boolean< Detail::HasNothrowMoveAssignment< T > > {};

template< typename T >
struct NoNothrowMoveAssignment : BooleanNot< Detail::HasNothrowMoveAssignment< T > > {};

} // namespace TypeOperate
} // namespace BR
