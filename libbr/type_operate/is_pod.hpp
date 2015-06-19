#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_IS_POD)
#  include <libbr/type_operate/is_scalar.hpp>
#  include <libbr/type_operate/is_void.hpp>
#endif // !BR_IS_POD

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_POD)

template< typename T >
using IsPOD = BooleanConstant< BR_IS_POD(T) >;

#else

template< typename T >
struct IsPOD : BooleanOr< IsScalar< T >, IsVoid< T > > {};

template< typename T >
struct IsPOD< T [] > : IsPOD< T > {};

template< typename T, Size S >
struct IsPOD< T [S] > : IsPOD< T > {};

#endif // BR_IS_POD

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsPOD : Boolean< Detail::TypeOperate::IsPOD< T > > {};

template< typename T >
struct NotPOD : BooleanNot< Detail::TypeOperate::IsPOD< T > > {};

} // namespace BR
