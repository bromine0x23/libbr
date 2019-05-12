/**
 * @file
 * @brief 整型特性类
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_transform/remove_const_volatile.hpp>
#include <libbr/utility/integral_constant.hpp>
#include <libbr/utility/type_wrapper.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief IntegerTraits
 * @tparam T
 */
template< typename T >
struct IntegerTraits;

} // namespace TypeTraits



namespace _ {
namespace TypeTraits {

template< typename T, Size bits, Boolean is_sign >
struct IntegerTraitsMin;

template< typename T, Size bits >
struct IntegerTraitsMin< T, bits, true > : public IntegralConstant< T, T(T(1) << bits) > {};

template< typename T, Size bits >
struct IntegerTraitsMin< T, bits, false > : public IntegralConstant< T, T(0) > {};

template< typename T, bool is_integral = IsIntegral<T>{} >
struct IntegerTraitsBasic {
	using Type = T;
	constexpr static auto is_integer = false;
	constexpr static auto is_signed  = false;
	constexpr static auto bits = 0;
	constexpr static auto min() noexcept -> Type { return T(); }
	constexpr static auto max() noexcept -> Type { return T(); }
};

template< typename TInteger >
struct IntegerTraitsBasic< TInteger, true > {
	using Type = TInteger;
	constexpr static bool is_integer = true;
	constexpr static bool is_signed  = static_cast<Type>(-1) < static_cast<Type>(0);
	constexpr static auto bits = static_cast<Size>(sizeof(Type) * BIT_PER_CHAR - is_signed);
	constexpr static auto min() noexcept -> Type { return IntegerTraitsMin< Type, bits, is_signed >(); }
	constexpr static auto max() noexcept -> Type { return is_signed ? Type(Type(~0) ^ min()) : Type(~0); }
};

template<>
struct IntegerTraitsBasic< bool, true > {
	using Type = bool;
	constexpr static bool is_integer = true;
	constexpr static bool is_signed  = false;
	constexpr static auto bits = 1;
	constexpr static auto min() noexcept -> Type { return false; }
	constexpr static auto max() noexcept -> Type { return true; }
};

template< typename T >
using IntegerTraits = IntegerTraitsBasic< RemoveConstVolatile<T> >;

} // namespace TypeTraits
} // namespace _

inline namespace TypeTraits {

template< typename T >
struct IntegerTraits : public TypeWrapper<T> {
	constexpr static auto is_integer = _::TypeTraits::IntegerTraits<T>::is_integer;
	constexpr static auto is_signed  = _::TypeTraits::IntegerTraits<T>::is_signed;
	constexpr static auto bits       = _::TypeTraits::IntegerTraits<T>::bits;
	constexpr static auto min() noexcept -> T { return _::TypeTraits::IntegerTraits<T>::min(); }
	constexpr static auto max() noexcept -> T { return _::TypeTraits::IntegerTraits<T>::max(); }
};

} // namespace TypeTraits

} // namespace BR


