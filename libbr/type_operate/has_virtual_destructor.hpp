#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_HAS_VIRTUAL_DESTRUCTOR)

template< typename T >
using HasVirtualDestructor = BooleanConstant< BR_TYPE_OPERATE_HAS_VIRTUAL_DESTRUCTOR(T) >;

#else

template< typename T >
using HasVirtualDestructor = BooleanFalse;

#endif // BR_TYPE_OPERATE_HAS_VIRTUAL_DESTRUCTOR

} // namespace Detail

template< typename T >
struct HasVirtualDestructor : Boolean< Detail::HasVirtualDestructor< T > > {};

template< typename T >
struct NoVirtualDestructor : BooleanNot< Detail::HasVirtualDestructor< T > > {};

} // namespace TypeOperate
} // namespace BR
