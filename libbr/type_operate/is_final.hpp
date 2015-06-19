#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_IS_FINAL)

template< typename T >
using IsFinal = BooleanConstant< BR_IS_FINAL(T) >;

#else

template< typename T >
using IsFinal = BooleanFalse;

#endif // BR_IS_FINAL

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsFinal : Boolean< Detail::TypeOperate::IsFinal< T > > {};

template< typename T >
struct NotFinal : BooleanNot< Detail::TypeOperate::IsFinal< T > > {};

} // namespace BR