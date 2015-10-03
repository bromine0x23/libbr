#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>

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
struct HasVirtualDestructor : BooleanRewrapPositive< Detail::TypeOperate::HasVirtualDestructor< T > > {};

template< typename T >
struct NoVirtualDestructor : BooleanRewrapNegative< Detail::TypeOperate::HasVirtualDestructor< T > > {};

} // namespace BR
