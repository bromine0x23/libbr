#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_UNION)

template< typename T >
using IsUnion = BooleanConstant< BR_IS_UNION(T) >;

#else

template< typename T >
using IsUnion = BooleanFalse;

#endif // BR_IS_UNION

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsUnion : Boolean< Detail::TypeOperate::IsUnion< T > > {};

template< typename T >
struct NotUnion : BooleanNot< Detail::TypeOperate::IsUnion< T > > {};

} // namespace BR

