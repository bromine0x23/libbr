#pragma once

#include <climits>

#include <libbr/config.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>

namespace BR {

inline namespace TypeTraits {

/**
 * @brief IntegerTraits
 * @tparam T
 */
template< typename T >
struct IntegerTraits;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T, bool is_integral = IsIntegral<T>{} >
struct IntegerTraitsBasic {
	using Type = T;
	constexpr static auto is_integer = false;
	constexpr static auto is_signed  = false;
	constexpr static auto digits = 0;
	constexpr static auto min() noexcept -> Type { return T(); }
	constexpr static auto max() noexcept -> Type { return T(); }
};

template< typename TInteger >
struct IntegerTraitsBasic< TInteger, true > {
	using Type = TInteger;
	constexpr static bool is_integer = true;
	constexpr static bool is_signed  = static_cast<Type>(-1) < static_cast<Type>(0);
	constexpr static auto digits = static_cast<Size>(sizeof(Type) * BIT_PER_CHAR - is_signed);
	constexpr static auto min() noexcept -> Type { return static_cast<Type>(is_signed ? Type(1) << digits : 0); }
	constexpr static auto max() noexcept -> Type { return static_cast<Type>(is_signed ? Type(~0) ^ min() : Type(~0)); }
};

template<>
struct IntegerTraitsBasic< bool, true > {
	using Type = bool;
	constexpr static bool is_integer = true;
	constexpr static bool is_signed  = false;
	constexpr static auto digits = 1;
	constexpr static auto min() noexcept -> Type { return false; }
	constexpr static auto max() noexcept -> Type { return true; }
};

template< typename T >
using IntegerTraits = IntegerTraitsBasic< RemoveConstVolatile<T> >;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IntegerTraits : public Detail::TypeTraits::IntegerTraits<T> {
};

} // namespace TypeTraits

} // namespace BR


