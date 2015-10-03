#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_HAS_NOTHROW_DEFAULT_CONSTRUCTOR)
#  include <libbr/type_operate/has_trivial_default_constructor.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_NOTHROW_DEFAULT_CONSTRUCTOR)

template< typename T >
using HasNothrowDefaultConstructor = BooleanConstant< BR_HAS_NOTHROW_DEFAULT_CONSTRUCTOR(T) >;

#else

template< typename T >
using HasNothrowDefaultConstructor = HasTrivialDefaultConstructor< T >;

#endif // BR_HAS_NOTHROW_DEFAULT_CONSTRUCTOR

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasNothrowDefaultConstructor : BooleanRewrapPositive< Detail::TypeOperate::HasNothrowDefaultConstructor< T > > {};

template< typename T >
struct NoNothrowDefaultConstructor : BooleanRewrapNegative< Detail::TypeOperate::HasNothrowDefaultConstructor< T > > {};

} // namespace BR
