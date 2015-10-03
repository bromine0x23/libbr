#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_traits/intrinsics.hpp>
#if !defined(BR_HAS_NOTHROW_MOVE_CONSTRUCTOR)
#  include <libbr/type_operate/has_trivial_move_constructor.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_NOTHROW_MOVE_CONSTRUCTOR)

template< typename T >
using HasNothrowMoveConstructor = BooleanConstant< BR_HAS_NOTHROW_MOVE_CONSTRUCTOR(T) >;

#else

template< typename T >
using HasNothrowMoveConstructor = HasTrivialMoveConstructor< T >;

#endif // BR_HAS_NOTHROW_MOVE_CONSTRUCTOR

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasNothrowMoveConstructor : BooleanRewrapPositive< Detail::TypeOperate::HasNothrowMoveConstructor< T > > {};

template< typename T >
struct NoNothrowMoveConstructor : BooleanRewrapNegative< Detail::TypeOperate::HasNothrowMoveConstructor< T > > {};

} // namespace BR

