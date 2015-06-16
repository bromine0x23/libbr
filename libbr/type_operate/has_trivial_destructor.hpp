#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_HAS_TRIVIAL_DESTRUCTOR)
#  include <libbr/type_operate/is_pod.hpp>
#endif

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_HAS_TRIVIAL_DESTRUCTOR)

template< typename T >
using HasTrivialDestructor = BooleanConstant< BR_TYPE_OPERATE_HAS_TRIVIAL_DESTRUCTOR(T) >;

#else

template< typename T >
using HasTrivialDestructor = IsPod< T >;

#endif // BR_TYPE_OPERATE_HAS_TRIVIAL_DESTRUCTOR

} // namespace Detail

template< typename T >
struct HasTrivialDestructor : Boolean< Detail::HasTrivialDestructor< T > > {};

template< typename T >
struct NoTrivialDestructor : BooleanNot< Detail::HasTrivialDestructor< T > > {};

} // namespace TypeOperate
} // namespace BR