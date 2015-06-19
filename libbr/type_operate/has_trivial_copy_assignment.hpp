#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_HAS_TRIVIAL_COPY_ASSIGNMENT)
#  include <libbr/type_operate/is_const.hpp>
#  include <libbr/type_operate/is_pod.hpp>
#  include <libbr/type_operate/is_volatile.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_TRIVIAL_COPY_ASSIGNMENT)

template< typename T >
using HasTrivialCopyAssignment = BooleanConstant< BR_HAS_TRIVIAL_COPY_ASSIGNMENT(T) >;

#else

template< typename T >
using HasTrivialCopyAssignment = BooleanAnd< IsPOD< T >, NotVolatile< T >, NotConst< T > >;

#endif // BR_HAS_TRIVIAL_COPY_ASSIGNMENT

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasTrivialCopyAssignment : Boolean< Detail::TypeOperate::HasTrivialCopyAssignment< T > > {};

template< typename T >
struct NoTrivialCopyAssignment : BooleanNot< Detail::TypeOperate::HasTrivialCopyAssignment< T > > {};

} // namespace BR