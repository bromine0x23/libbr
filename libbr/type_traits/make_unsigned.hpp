/**
 * @file
 * @brief 将整数类型转换成对应的无符号整数类型
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type.hpp>
#include <libbr/assert/dummy_false.hpp>
#include <libbr/type_traits/is_enum.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/map_cv.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>

namespace BR {

inline namespace TypeTraits {

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

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct TypeMakeUnsignedInteger : public TypeWrapper<T> {};

template<>
struct TypeMakeUnsignedInteger< char > : public TypeWrapper< unsigned char > {};

template<>
struct TypeMakeUnsignedInteger< signed char > : public TypeWrapper< unsigned char > {};

template<>
struct TypeMakeUnsignedInteger< signed short > : public TypeWrapper< unsigned short > {};

template<>
struct TypeMakeUnsignedInteger< signed int > : public TypeWrapper< unsigned int > {};

template<>
struct TypeMakeUnsignedInteger< signed long > : public TypeWrapper< unsigned long > {};

template<>
struct TypeMakeUnsignedInteger< signed long long > : public TypeWrapper< unsigned long long > {};

#if defined(BR_HAS_INT128)

template<>
struct TypeMakeUnsignedInteger<SInt128> : public TypeWrapper<UInt128> {};

template< Size size >
struct TypeMakeUnsignedEnum : public TypeWrapper<UInt128> {};

template<>
struct TypeMakeUnsignedEnum< sizeof(UInt64) > : TypeWrapper<UInt64> {};

#else

template< Size size >
struct TypeMakeUnsignedEnum : public TypeWrapper<UInt64> {};

#endif // defined(BR_HAS_INT128)

template<> struct TypeMakeUnsignedEnum< sizeof(UInt8) > : public TypeWrapper<UInt8> {};

template<> struct TypeMakeUnsignedEnum< sizeof(UInt16) > : public TypeWrapper<UInt16> {};

template<> struct TypeMakeUnsignedEnum< sizeof(UInt32) > : public TypeWrapper<UInt32> {};

template< typename T, bool is_integral = IsIntegral<T>{}, bool is_enum = IsEnum<T>{} >
struct TypeMakeUnsignedBasic;

template< typename T >
struct TypeMakeUnsignedBasic< T, false, false > {
	static_assert(DummyFalse<T>{}, "Type must be integer type (except bool), or an enumeration type.");
};

template< typename T >
struct TypeMakeUnsignedBasic< T, true, false > : TypeMakeUnsignedInteger<T> {
	static_assert(NotSame< T, bool >{}, "Type must be integer type (except bool), or an enumeration type.");
};

template< typename T >
struct TypeMakeUnsignedBasic< T, false, true > : TypeMakeUnsignedEnum< sizeof(T) > {};

template< typename T >
struct TypeMakeUnsignedBasic< T, true, true > {
	static_assert(DummyFalse<T>{}, "[Fatal Error] Type cannot be both integer type and enumeration type.");
};

template< typename T >
struct TypeMakeUnsigned : public TypeMapCV< T, TypeUnwrap< TypeMakeUnsignedBasic< RemoveConstVolatile<T> > > > {};

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct TypeMakeUnsigned : public TypeRewrap< Detail::TypeTraits::TypeMakeUnsigned<T> > {};

} // namespace TypeTraits

} // namespace BR