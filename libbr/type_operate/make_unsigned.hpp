#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/is_enum.hpp>
#include <libbr/type_operate/is_integer.hpp>
#include <libbr/type_operate/is_same.hpp>
#include <libbr/type_operate/is_unsigned.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeMakeUnsignedInteger : TypeWrapper< T > {};

template<> struct TypeMakeUnsignedInteger<        char      > : TypeWrapper< unsigned char      > {};
template<> struct TypeMakeUnsignedInteger< signed char      > : TypeWrapper< unsigned char      > {};
template<> struct TypeMakeUnsignedInteger< signed short     > : TypeWrapper< unsigned short     > {};
template<> struct TypeMakeUnsignedInteger< signed int       > : TypeWrapper< unsigned int       > {};
template<> struct TypeMakeUnsignedInteger< signed long      > : TypeWrapper< unsigned long      > {};
template<> struct TypeMakeUnsignedInteger< signed long long > : TypeWrapper< unsigned long long > {};

#if defined(BR_HAS_INT128)
template<> struct TypeMakeUnsignedInteger< SInt128 > : TypeWrapper< UInt128 > {};
#endif

template< Size size >
struct TypeMakeUnsignedEnum : TypeWrapper< UInt64 > {};

template<> struct TypeMakeUnsignedEnum< sizeof(UInt8 ) > : TypeWrapper< UInt8  > {};
template<> struct TypeMakeUnsignedEnum< sizeof(UInt16) > : TypeWrapper< UInt16 > {};
template<> struct TypeMakeUnsignedEnum< sizeof(UInt32) > : TypeWrapper< UInt32 > {};

template< typename T >
struct TypeMakeUnsignedBasic : Conditional<
	IsUnsigned< T >,
	TypeWrapper< T >,
	Conditional<
		IsInteger< T >,
		TypeMakeUnsignedInteger< T >,
		TypeMakeUnsignedEnum< sizeof(T) >
	>
> {
	static_assert(
		BooleanAnd<
			BooleanOr< IsInteger< T >, IsEnum< T > >,
			NotSame< T, bool >
		>::value,
		"Type must be integer type (except bool), or an enumeration type."
	);
};

template< typename T >
struct TypeMakeUnsigned : TypeMakeUnsignedBasic< RemoveConstVolatile< T > > {};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct TypeMakeUnsigned : TypeRewrap< Detail::TypeOperate::TypeMakeUnsigned< T > > {};

template< typename T >
using MakeUnsigned = TypeUnwrap< TypeMakeUnsigned< T > >;

} // namespace BR