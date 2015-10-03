#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_HAS_NOTHROW_MOVE_ASSIGNMENT)
#  include <libbr/type_operate/has_trivial_move_assignment.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_NOTHROW_MOVE_ASSIGNMENT)

template< typename T >
using HasNothrowMoveAssignment = BooleanConstant< BR_HAS_NOTHROW_MOVE_ASSIGNMENT(T) >;

#else

template< typename T >
using HasNothrowMoveAssignment = HasTrivialMoveAssignment< T >;

#endif // BR_HAS_NOTHROW_MOVE_ASSIGNMENT

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasNothrowMoveAssignment : BooleanRewrapPositive< Detail::TypeOperate::HasNothrowMoveAssignment< T > > {};

template< typename T >
struct NoNothrowMoveAssignment : BooleanRewrapNegative< Detail::TypeOperate::HasNothrowMoveAssignment< T > > {};

} // namespace BR
