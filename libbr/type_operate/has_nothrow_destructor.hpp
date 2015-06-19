#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/intrinsics.hpp>
#if !defined(BR_HAS_NOTHROW_DESTRUCTOR)
#  include <libbr/type_operate/is_const.hpp>
#  include <libbr/type_operate/is_reference.hpp>
#  include <libbr/type_operate/is_volatile.hpp>
#  include <libbr/utility/make_value.hpp>
#endif

namespace BR {

namespace Detail {
namespace TypeOperate {

#if defined(BR_HAS_NOTHROW_DESTRUCTOR)

template< typename T >
using HasNothrowDestructor = BooleanConstant< BR_HAS_NOTHROW_DESTRUCTOR(T) >;

#else

template< typename T >
using HasNothrowDestructorBasic = BooleanConstant< noexcept(make_rvalue< T & >().~T()) >;

template< typename T >
using HasNothrowDestructor = BooleanAnd< NotConst< T >, NotVolatile< T >, NotReference< T >, HasNothrowDestructorBasic< T >  >;

#endif // BR_HAS_NOTHROW_DESTRUCTOR

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct HasNothrowDestructor : Boolean< Detail::TypeOperate::HasNothrowDestructor< T > > {};

template< typename T >
struct NoNothrowDestructor : BooleanNot< Detail::TypeOperate::HasNothrowDestructor< T > > {};

} // namespace BR