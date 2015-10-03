#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_HAS_NOTHROW_COPY_CONSTRUCTOR)
#  include <libbr/type_operate/has_trivial_copy_constructor.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_NOTHROW_COPY_CONSTRUCTOR)

template< typename T >
using HasNothrowCopyConstructor = BooleanConstant< BR_HAS_NOTHROW_COPY_CONSTRUCTOR(T) >;

#else

template< typename T >
using HasNothrowCopyConstructor = HasTrivialCopyAssignment< T >;

#endif // BR_HAS_NOTHROW_COPY_CONSTRUCTOR

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasNothrowCopyConstructor : BooleanRewrapPositive< Detail::TypeOperate::HasNothrowCopyConstructor< T > > {};

template< typename T >
struct NoNothrowCopyConstructor : BooleanRewrapNegative< Detail::TypeOperate::HasNothrowCopyConstructor< T > > {};

} // namespace BR