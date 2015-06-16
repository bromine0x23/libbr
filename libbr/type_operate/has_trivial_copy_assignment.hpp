#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_ASSIGNMENT)
#  include <libbr/type_operate/is_const.hpp>
#  include <libbr/type_operate/is_pod.hpp>
#  include <libbr/type_operate/is_volatile.hpp>
#endif

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_ASSIGNMENT)

template< typename T >
using HasTrivialCopyAssignment = BooleanConstant< BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_ASSIGNMENT(T) >;

#else

template< typename T >
using HasTrivialCopyAssignment = BooleanAnd< IsPod< T >, NotVolatile< T >, NotConst< T > >;

#endif // BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_ASSIGNMENT

} // namespace Detail

template< typename T >
struct HasTrivialCopyAssignment : Boolean< Detail::HasTrivialCopyAssignment< T > > {};

template< typename T >
struct NoTrivialCopyAssignment : BooleanNot< Detail::HasTrivialCopyAssignment< T > > {};

} // namespace TypeOperate
} // namespace BR