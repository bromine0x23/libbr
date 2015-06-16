#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/is_enum.hpp>
#include <libbr/type_operate/is_integer.hpp>
#include <libbr/type_operate/is_same.hpp>
#include <libbr/type_operate/is_signed.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {
namespace TypeOperate {

namespace Detail {

template< typename T >
struct TypeMakeSignedInteger : TypeWrapper< T > {};

template<>
struct TypeMakeSignedInteger< char > : TypeWrapper< signed char > {};

template<>
struct TypeMakeSignedInteger< unsigned char > : TypeWrapper< signed char > {};

template<>
struct TypeMakeSignedInteger< unsigned short > : TypeWrapper< signed short > {};

template<>
struct TypeMakeSignedInteger< unsigned int > : TypeWrapper< signed int > {};

template<>
struct TypeMakeSignedInteger< unsigned long > : TypeWrapper< signed long > {};

template<>
struct TypeMakeSignedInteger< unsigned long long > : TypeWrapper< signed long long > {};

template< Size size >
struct TypeMakeSignedEnum : TypeWrapper< SInt64 > {};

template<>
struct TypeMakeSignedEnum< sizeof(SInt8) > : TypeWrapper< SInt8 > {};

template<>
struct TypeMakeSignedEnum< sizeof(SInt16) > : TypeWrapper< SInt16 > {};

template<>
struct TypeMakeSignedEnum< sizeof(SInt32) > : TypeWrapper< SInt32 > {};

template< typename T >
struct TypeMakeSignedBasic : Conditional<
	IsSigned< T >,
	TypeWrapper< T >,
	Conditional<
		IsInteger< T >,
		TypeMakeSignedInteger< T >,
		TypeMakeSignedEnum< sizeof(T) >
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
struct TypeMakeSigned : TypeMakeSignedBasic< RemoveConstVolatile< T > > {};

} // namespace Detail

template< typename T >
struct TypeMakeSigned : TypeRewrap< Detail::TypeMakeSigned< T > > {};

template< typename T >
using MakeSigned = TypeUnwrap< TypeMakeSigned< T > >;

} // namespace TypeOperate
} // namespace BR