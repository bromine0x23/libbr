#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_HAS_TRIVIAL_DESTRUCTOR)
#  include <libbr/type_operate/is_pod.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_TRIVIAL_DESTRUCTOR)

template< typename T >
using HasTrivialDestructor = BooleanConstant< BR_HAS_TRIVIAL_DESTRUCTOR(T) >;

#else

template< typename T >
using HasTrivialDestructor = IsPOD< T >;

#endif // BR_HAS_TRIVIAL_DESTRUCTOR

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasTrivialDestructor : Boolean< Detail::TypeOperate::HasTrivialDestructor< T > > {};

template< typename T >
struct NoTrivialDestructor : BooleanNot< Detail::TypeOperate::HasTrivialDestructor< T > > {};

} // namespace BR