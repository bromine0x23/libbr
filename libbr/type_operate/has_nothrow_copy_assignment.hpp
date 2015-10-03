#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_HAS_NOTHROW_COPY_ASSIGNMENT)
#  include <libbr/type_operate/has_trivial_copy_assignment.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_NOTHROW_COPY_ASSIGNMENT)

template< typename T >
using HasNothrowCopyAssignment = BooleanConstant< BR_HAS_NOTHROW_COPY_ASSIGNMENT(T) >;

#else

template< typename T >
using HasNothrowCopyAssignment = HasTrivialCopyAssignment< T >;

#endif // BR_HAS_NOTHROW_COPY_ASSIGNMENT

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasNothrowCopyAssignment : BooleanRewrapPositive< Detail::TypeOperate::HasNothrowCopyAssignment< T > > {};

template< typename T >
struct NoNothrowCopyAssignment : BooleanRewrapNegative< Detail::TypeOperate::HasNothrowCopyAssignment< T > > {};

} // namespace BR
