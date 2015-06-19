#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_integer.hpp>
#include <libbr/type_operate/is_enum.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct IsSignedBasic {
	using Type = RemoveConstVolatile< T >;
	constexpr static auto value = static_cast< Type >(-1) < static_cast< Type >(0);
};

template< typename T >
using IsSigned = BooleanAnd< BooleanOr< IsInteger< T >, IsEnum< T > >, BooleanConstant< IsSignedBasic< T >::value > >;

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct IsSigned : Boolean< Detail::TypeOperate::IsSigned< T > > {};

template< typename T >
struct NotSigned : BooleanNot< Detail::TypeOperate::IsSigned< T > > {};

} // namespace BR