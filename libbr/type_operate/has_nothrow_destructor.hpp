#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_TYPE_OPERATE_HAS_NOTHROW_DESTRUCTOR)
#  include <libbr/type_operate/is_const.hpp>
#  include <libbr/type_operate/is_reference.hpp>
#  include <libbr/type_operate/is_volatile.hpp>
#  include <libbr/utility/make_value.hpp>
#endif

namespace BR {
namespace TypeOperate {

namespace Detail {

#if defined(BR_TYPE_OPERATE_HAS_NOTHROW_DESTRUCTOR)

template< typename T >
using HasNothrowDestructor = BooleanConstant< BR_TYPE_OPERATE_HAS_NOTHROW_DESTRUCTOR(T) >;

#else

template< typename T >
using HasNothrowDestructorBasic = BooleanConstant< noexcept(make_rvalue< T & >().~T()) >;

template< typename T >
using HasNothrowDestructor = BooleanAnd< NotConst< T >, NotVolatile< T >, NotReference< T >, HasNothrowDestructorBasic< T >  >;

#endif // BR_TYPE_OPERATE_HAS_NOTHROW_DESTRUCTOR

} // namespace Detail

template< typename T >
struct HasNothrowDestructor : Boolean< Detail::HasNothrowDestructor< T > > {};

template< typename T >
struct NoNothrowDestructor : BooleanNot< Detail::HasNothrowDestructor< T > > {};

} // namespace TypeOperate
} // namespace BR