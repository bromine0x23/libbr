#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_HAS_TRIVIAL_COPY_CONSTRUCTOR)
#  include <libbr/type_traits/is_pod.hpp>
#  include <libbr/type_traits/is_volatile.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_TRIVIAL_COPY_CONSTRUCTOR)

template< typename T >
using HasTrivialCopyConstructor = BooleanConstant< BR_HAS_TRIVIAL_COPY_CONSTRUCTOR(T) >;

#else

template< typename T >
using HasTrivialCopyConstructor = BooleanAnd< IsPOD< T >, NotVolatile< T > >;

#endif // BR_HAS_TRIVIAL_COPY_CONSTRUCTOR

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasTrivialCopyConstructor : BooleanRewrapPositive< Detail::TypeOperate::HasTrivialCopyConstructor< T > > {};

template< typename T >
struct NoTrivialCopyConstructor : BooleanRewrapNegative< Detail::TypeOperate::HasTrivialCopyConstructor< T > > {};

} // namespace BR