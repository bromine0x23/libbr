#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_HAS_NOTHROW_MOVE_CONSTRUCTOR)
#  include <libbr/type_operate/has_trivial_move_constructor.hpp>
#endif

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_HAS_NOTHROW_MOVE_CONSTRUCTOR)

template< typename T >
using HasNothrowMoveConstructor = BooleanConstant< BR_TYPE_OPERATE_HAS_NOTHROW_MOVE_CONSTRUCTOR(T) >;

#else

template< typename T >
using HasNothrowMoveConstructor = HasTrivialMoveConstructor< T >;

#endif // BR_TYPE_OPERATE_HAS_NOTHROW_MOVE_CONSTRUCTOR

} // namespace Detail

template< typename T >
struct HasNothrowMoveConstructor : Boolean< Detail::HasNothrowMoveConstructor< T > > {};

template< typename T >
struct NoNothrowMoveConstructor : BooleanNot< Detail::HasNothrowMoveConstructor< T > > {};

} // namespace TypeOperate
} // namespace BR

