/**
 * @file
 * @brief 将整数类型转换成对应的有符号整数类型
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_enum.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_transform/copy_const_volatile.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTransform {

/**
 * @brief 将 \em T 转换成对应的有符号整数类型
 * @tparam T
 * @see TypeWrapper
 * @see MakeSigned
 *
 * 包装整型类型或枚举类型 \em T 对应的的有符号整型类型
 */
template< typename T >
struct TypeMakeSigned;

/**
 * @brief TypeMakeSigned 的简写版本
 * @tparam T
 * @see TypeMakeSigned
 */
template< typename T >
using MakeSigned = TypeUnwrap< TypeMakeSigned<T> >;

} // namespace TypeTransform



namespace _ {
namespace TypeTransform {

template< typename T >
struct TypeMakeSignedInteger : public TypeWrapper<T> {};

template<>
struct TypeMakeSignedInteger< char > : public TypeWrapper< signed char > {};

template<>
struct TypeMakeSignedInteger< unsigned char > : public TypeWrapper< signed char > {};

template<>
struct TypeMakeSignedInteger< unsigned short > : public TypeWrapper< signed short > {};

template<>
struct TypeMakeSignedInteger< unsigned int > : public TypeWrapper< signed int > {};

template<>
struct TypeMakeSignedInteger< unsigned long > : public TypeWrapper< signed long > {};

template<>
struct TypeMakeSignedInteger< unsigned long long > : public TypeWrapper< signed long long > {};

#if defined(BR_HAS_INT128)

template<>
struct TypeMakeSignedInteger<UInt128> : public TypeWrapper<SInt128> {};

template< Size size >
struct TypeMakeSignedEnum : public TypeWrapper<SInt128> {};

template<>
struct TypeMakeSignedEnum< sizeof(SInt64) > : TypeWrapper<SInt64> {};

#else

template< Size size >
struct TypeMakeSignedEnum : public TypeWrapper<SInt64> {};

#endif // defined(BR_HAS_INT128)

template<> struct TypeMakeSignedEnum< sizeof(SInt8) > : public TypeWrapper<SInt8> {};

template<> struct TypeMakeSignedEnum< sizeof(SInt16) > : public TypeWrapper<SInt16> {};

template<> struct TypeMakeSignedEnum< sizeof(SInt32) > : public TypeWrapper<SInt32> {};

template< typename T, bool is_integral = IsIntegral<T>{}, bool is_enum = IsEnum<T>{} >
struct TypeMakeSignedBasic {
	static_assert(is_integral != is_enum, "Type must be either integer type (except bool) or an enumeration type.");
};

template< typename T >
struct TypeMakeSignedBasic< T, true, false > : TypeMakeSignedInteger<T> {
	static_assert(NotSame< T, bool >{}, "Type must be either integer type (except bool) or an enumeration type.");
};

template< typename T >
struct TypeMakeSignedBasic< T, false, true > : TypeMakeSignedEnum< sizeof(T) > {};


template< typename T >
struct TypeMakeSigned : public TypeCopyConstVolatile< T, TypeUnwrap< TypeMakeSignedBasic< RemoveConstVolatile<T> > > > {};

} // namespace TypeTransform
} // namespace _

inline namespace TypeTransform {

template< typename T >
struct TypeMakeSigned : public TypeRewrap< _::TypeTransform::TypeMakeSigned<T> > {};

} // namespace TypeTransform

} // namespace BR