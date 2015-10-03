#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_HAS_TRIVIAL_COPY_ASSIGNMENT)
#  include <libbr/type_traits/is_const.hpp>
#  include <libbr/type_traits/is_pod.hpp>
#  include <libbr/type_traits/is_volatile.hpp>
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
struct HasTrivialCopyAssignment : BooleanRewrapPositive< Detail::TypeOperate::HasTrivialCopyAssignment< T > > {};

template< typename T >
struct NoTrivialCopyAssignment : BooleanRewrapNegative< Detail::TypeOperate::HasTrivialCopyAssignment< T > > {};

} // namespace BR