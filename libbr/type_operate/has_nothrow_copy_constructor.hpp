#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_HAS_NOTHROW_COPY_CONSTRUCTOR)
#  include <libbr/type_operate/has_trivial_copy_constructor.hpp>
#endif

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_HAS_NOTHROW_COPY_CONSTRUCTOR)

template< typename T >
using HasNothrowCopyConstructor = BooleanConstant< BR_TYPE_OPERATE_HAS_NOTHROW_COPY_CONSTRUCTOR(T) >;

#else

template< typename T >
using HasNothrowCopyConstructor = HasTrivialCopyAssignment< T >;

#endif // BR_TYPE_OPERATE_HAS_NOTHROW_COPY_CONSTRUCTOR

} // namespace Detail

template< typename T >
struct HasNothrowCopyConstructor : Boolean< Detail::HasNothrowCopyConstructor< T > > {};

template< typename T >
struct NoNothrowCopyConstructor : BooleanNot< Detail::HasNothrowCopyConstructor< T > > {};

} // namespace TypeOperate
} // namespace BR