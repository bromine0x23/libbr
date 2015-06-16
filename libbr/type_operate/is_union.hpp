#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_IS_UNION)

template< typename T >
using IsUnion = BooleanConstant< BR_TYPE_OPERATE_IS_UNION(T) >;

#else

template< typename T >
using IsUnion = BooleanFalse;

#endif // BR_TYPE_OPERATE_IS_UNION

} // namespace Detail

template< typename T >
struct IsUnion : Boolean< Detail::IsUnion< T > > {};

template< typename T >
struct NotUnion : BooleanNot< Detail::IsUnion< T > > {};

} // namespace TypeOperate
} // namespace BR

