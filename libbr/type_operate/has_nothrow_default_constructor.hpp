#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_HAS_NOTHROW_DEFAULT_CONSTRUCTOR)
#  include <libbr/type_operate/has_trivial_default_constructor.hpp>
#endif

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_HAS_NOTHROW_DEFAULT_CONSTRUCTOR)

template< typename T >
using HasNothrowDefaultConstructor = BooleanConstant< BR_TYPE_OPERATE_HAS_NOTHROW_DEFAULT_CONSTRUCTOR(T) >;

#else

template< typename T >
using HasNothrowDefaultConstructor = HasTrivialDefaultConstructor< T >;

#endif // BR_TYPE_OPERATE_HAS_NOTHROW_DEFAULT_CONSTRUCTOR

} // namespace Detail

template< typename T >
struct HasNothrowDefaultConstructor : Boolean< Detail::HasNothrowDefaultConstructor< T > > {};

template< typename T >
struct NoNothrowDefaultConstructor : BooleanNot< Detail::HasNothrowDefaultConstructor< T > > {};

} // namespace TypeOperate
} // namespace BR
