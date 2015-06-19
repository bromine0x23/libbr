#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_VIRTUAL_DESTRUCTOR)

template< typename T >
using HasVirtualDestructor = BooleanConstant< BR_HAS_VIRTUAL_DESTRUCTOR(T) >;

#else

template< typename T >
using HasVirtualDestructor = BooleanFalse;

#endif // BR_HAS_VIRTUAL_DESTRUCTOR

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasVirtualDestructor : Boolean< Detail::TypeOperate::HasVirtualDestructor< T > > {};

template< typename T >
struct NoVirtualDestructor : BooleanNot< Detail::TypeOperate::HasVirtualDestructor< T > > {};

} // namespace BR
