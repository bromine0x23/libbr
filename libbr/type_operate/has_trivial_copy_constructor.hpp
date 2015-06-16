#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_CONSTRUCTOR)
#  include <libbr/type_operate/is_pod.hpp>
#  include <libbr/type_operate/is_volatile.hpp>
#endif

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_CONSTRUCTOR)

template< typename T >
using HasTrivialCopyConstructor = BooleanConstant< BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_CONSTRUCTOR(T) >;

#else

template< typename T >
using HasTrivialCopyConstructor = BooleanAnd< IsPod< T >, NotVolatile< T > >;

#endif // BR_TYPE_OPERATE_HAS_TRIVIAL_COPY_CONSTRUCTOR

} // namespace Detail

template< typename T >
struct HasTrivialCopyConstructor : Boolean< Detail::HasTrivialCopyConstructor< T > > {};

template< typename T >
struct NoTrivialCopyConstructor : BooleanNot< Detail::HasTrivialCopyConstructor< T > > {};

} // namespace TypeOperate
} // namespace BR