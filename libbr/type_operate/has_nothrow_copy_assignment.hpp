#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_HAS_NOTHROW_COPY_ASSIGNMENT)
#  include <libbr/type_operate/has_trivial_copy_assignment.hpp>
#endif

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_HAS_NOTHROW_COPY_ASSIGNMENT)

template< typename T >
using HasNothrowCopyAssignment = BooleanConstant< BR_TYPE_OPERATE_HAS_NOTHROW_COPY_ASSIGNMENT(T) >;

#else

template< typename T >
using HasNothrowCopyAssignment = HasTrivialCopyAssignment< T >;

#endif // BR_TYPE_OPERATE_HAS_NOTHROW_COPY_ASSIGNMENT

} // namespace Detail

template< typename T >
struct HasNothrowCopyAssignment : Boolean< Detail::HasNothrowCopyAssignment< T > > {};

template< typename T >
struct NoNothrowCopyAssignment : BooleanNot< Detail::HasNothrowCopyAssignment< T > > {};

} // namespace TypeOperate
} // namespace BR
