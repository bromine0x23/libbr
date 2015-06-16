#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_member_pointer.hpp>
#include <libbr/type_operate/is_member_function_pointer.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct IsMemberObjectPointer : BooleanAnd< IsMemberPointer< T >, NotMemberFunctionPointer< T > > {};

} // namespace Detail

template< typename T >
struct IsMemberObjectPointer : Boolean< Detail::IsMemberObjectPointer< T > > {};

template< typename T >
struct NotMemberObjectPointer : BooleanNot< Detail::IsMemberObjectPointer< T > > {};

} // namespace TypeOperate
} // namespace BR
