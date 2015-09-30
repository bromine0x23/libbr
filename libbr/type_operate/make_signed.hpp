/**
 * @file
 * @brief 将整数类型转换成对应的有符号整数类型
 * @author Bromine0x23
 * @since 2015/6/16
 */
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

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeMakeSignedInteger : TypeWrapper< T > {};

template<> struct TypeMakeSignedInteger<          char      > : TypeWrapper< signed char      > {};
template<> struct TypeMakeSignedInteger< unsigned char      > : TypeWrapper< signed char      > {};
template<> struct TypeMakeSignedInteger< unsigned short     > : TypeWrapper< signed short     > {};
template<> struct TypeMakeSignedInteger< unsigned int       > : TypeWrapper< signed int       > {};
template<> struct TypeMakeSignedInteger< unsigned long      > : TypeWrapper< signed long      > {};
template<> struct TypeMakeSignedInteger< unsigned long long > : TypeWrapper< signed long long > {};

#if defined(BR_HAS_INT128)

template<> struct TypeMakeSignedInteger<UInt128> : TypeWrapper<SInt128> {};

template< Size size >
struct TypeMakeSignedEnum : TypeWrapper<SInt128> {};

template<> struct TypeMakeSignedEnum< sizeof(SInt64) > : TypeWrapper<SInt64> {};

#else

template< Size size >
struct TypeMakeSignedEnum : TypeWrapper<SInt64> {};

#endif // defined(BR_HAS_INT128)

template<> struct TypeMakeSignedEnum< sizeof(SInt8) > : TypeWrapper<SInt8> {};
template<> struct TypeMakeSignedEnum< sizeof(SInt16) > : TypeWrapper<SInt16> {};
template<> struct TypeMakeSignedEnum< sizeof(SInt32) > : TypeWrapper<SInt32> {};

template< typename T >
struct TypeMakeSignedBasic : Conditional<
	IsSigned<T>,
	TypeWrapper<T>,
	Conditional<
		IsInteger<T>,
		TypeMakeSignedInteger<T>,
		TypeMakeSignedEnum< sizeof(T) >
	>
> {
	static_assert(
		BooleanAnd<
			BooleanOr< IsInteger<T>, IsEnum<T> >,
			NotSame< T, bool >
		>::value,
		"Type must be integer type (except bool), or an enumeration type."
	);
};

template< typename T >
struct TypeMakeSigned : TypeMakeSignedBasic< RemoveConstVolatile<T> > {};

} // namespace TypeOperate
} // namespace Detail

/**
 * @brief 将 \em T 转换成对应的有符号整数类型
 * @tparam T
 * @see TypeWrapper
 * @see MakeSigned
 *
 * 包装整型类型或枚举类型 \em T 对应的的有符号整型类型
 */
template< typename T >
struct TypeMakeSigned : TypeRewrap< Detail::TypeOperate::TypeMakeSigned<T> > {};

/**
 * @brief TypeMakeSigned 的简写版本
 * @tparam T
 * @see TypeMakeSigned
 */
template< typename T >
using MakeSigned = TypeUnwrap< TypeMakeSigned<T> >;

} // namespace BR