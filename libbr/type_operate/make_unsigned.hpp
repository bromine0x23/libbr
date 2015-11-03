/**
 * @file
 * @brief 将整数类型转换成对应的无符号整数类型
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/type_traits/is_enum.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/is_unsigned.hpp>

namespace BR {

/**
 * @brief 将 \em T 转换成对应的无符号整型类型
 * @tparam T
 * @see TypeWrapper
 * @see MakeUnsigned
 *
 * 包装整型类型或枚举类型 \em T 对应的的无符号整型类型
 */
template< typename T >
struct TypeMakeUnsigned;

/**
 * @brief TypeMakeUnsigned 的简写版本
 * @tparam T
 * @see TypeMakeUnsigned
 */
template< typename T >
using MakeUnsigned = TypeUnwrap< TypeMakeUnsigned<T> >;

namespace Detail {
namespace TypeOperate {

template< typename T >
struct TypeMakeUnsignedInteger : public TypeWrapper<T> {
};

template<>
struct TypeMakeUnsignedInteger< char > : public TypeWrapper< unsigned char > {
};

template<>
struct TypeMakeUnsignedInteger< signed char > : public TypeWrapper< unsigned char > {
};

template<>
struct TypeMakeUnsignedInteger< signed short > : public TypeWrapper< unsigned short > {
};

template<>
struct TypeMakeUnsignedInteger< signed int > : public TypeWrapper< unsigned int > {
};

template<>
struct TypeMakeUnsignedInteger< signed long > : public TypeWrapper< unsigned long > {
};

template<>
struct TypeMakeUnsignedInteger< signed long long > : public TypeWrapper< unsigned long long > {
};

#if defined(BR_HAS_INT128)

template<>
struct TypeMakeUnsignedInteger<SInt128> : public TypeWrapper<UInt128> {
};

template< Size size >
struct TypeMakeUnsignedEnum : public TypeWrapper<UInt128> {
};

template<> struct TypeMakeUnsignedEnum< sizeof(UInt64) > : TypeWrapper<UInt64> {
};

#else

template< Size size >
struct TypeMakeUnsignedEnum : public TypeWrapper<UInt64> {
};

#endif // defined(BR_HAS_INT128)

template<> struct TypeMakeUnsignedEnum< sizeof(UInt8) > : public TypeWrapper<UInt8> {
};

template<> struct TypeMakeUnsignedEnum< sizeof(UInt16) > : public TypeWrapper<UInt16> {
};

template<> struct TypeMakeUnsignedEnum< sizeof(UInt32) > : public TypeWrapper<UInt32> {
};

template< typename T >
struct TypeMakeUnsignedBasic : public Conditional<
	IsUnsigned<T>,
	TypeWrapper<T>,
	Conditional<
		IsIntegral<T>,
		TypeMakeUnsignedInteger<T>,
		TypeMakeUnsignedEnum< sizeof(T) >
	>
> {
	static_assert(!BooleanAnd< NotIntegral<T>, NotEnum<T>, IsSame< T, bool > >::value, "Type must be integer type (except bool), or an enumeration type.");
};

template< typename T >
struct TypeMakeUnsigned : public TypeMakeUnsignedBasic< RemoveConstVolatile<T> > {
};

} // namespace TypeOperate
} // namespace Detail

template< typename T >
struct TypeMakeUnsigned : public TypeRewrap< Detail::TypeOperate::TypeMakeUnsigned<T> > {
};

} // namespace BR