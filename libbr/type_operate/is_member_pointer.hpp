#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_member_function_pointer.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsMemberPointer : IsMemberFunctionPointer< T > {};

template< typename TClass, typename TMember >
struct IsMemberPointer< TMember TClass::* > : BooleanTrue {};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsMemberPointer : Boolean< Detail::TypeOperate::IsMemberPointer< T > > {};

template< typename T >
struct NotMemberPointer : BooleanNot< Detail::TypeOperate::IsMemberPointer< T > > {};

} // namespace BR
