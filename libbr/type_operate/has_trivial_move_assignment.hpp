#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_HAS_TRIVIAL_MOVE_ASSIGNMENT)
#  include <libbr/type_traits/is_const.hpp>
#  include <libbr/type_traits/is_pod.hpp>
#  include <libbr/type_traits/is_volatile.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_TRIVIAL_MOVE_ASSIGNMENT)

template< typename T >
using HasTrivialMoveAssignment = BooleanConstant< BR_HAS_TRIVIAL_MOVE_ASSIGNMENT(T) >;

#else

template< typename T >
using HasTrivialMoveAssignment = BooleanAnd< IsPOD<T>, NotConst<T>, NotVolatile<T> >;

#endif // BR_HAS_TRIVIAL_MOVE_ASSIGNMENT

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasTrivialMoveAssignment : BooleanRewrapPositive< Detail::TypeOperate::HasTrivialMoveAssignment< T > > {};

template< typename T >
struct NoTrivialMoveAssignment : BooleanRewrapNegative< Detail::TypeOperate::HasTrivialMoveAssignment< T > > {};

} // namespace BR