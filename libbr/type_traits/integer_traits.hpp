#pragma once

#include <climits>

#include <libbr/config.hpp>
#include <libbr/type_traits/is_signed.hpp>
#include <libbr/type_traits/is_unsigned.hpp>

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

template< typename TInteger, TInteger min_val, TInteger max_val >
struct IntegerTraitsBasic {
	constexpr static TInteger min() noexcept { return min_val; }
	constexpr static TInteger max() noexcept { return max_val; }
	constexpr static auto is_integer  = true;
	constexpr static auto is_signed   = IsSigned< TInteger >::value;
	constexpr static auto is_unsigned = IsUnsigned< TInteger >::value;
};

} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct IntegerTraits {
	constexpr static T min() noexcept { return T(); }
	constexpr static T max() noexcept { return T(); }
	constexpr static auto is_integer  = false;
	constexpr static auto is_signed   = false;
	constexpr static auto is_unsigned = false;
};

template<>
struct IntegerTraits< char > : Detail::IntegerTraitsBasic< char, CHAR_MIN, CHAR_MAX > {};

template<>
struct IntegerTraits< signed char > : Detail::IntegerTraitsBasic< signed char, SCHAR_MIN, SCHAR_MAX > {};

template<>
struct IntegerTraits< unsigned char > : Detail::IntegerTraitsBasic< unsigned char, 0, UCHAR_MAX > {};

template<>
struct IntegerTraits< signed short > : Detail::IntegerTraitsBasic< signed short, SHRT_MIN, SHRT_MAX > {};

template<>
struct IntegerTraits< unsigned short > : Detail::IntegerTraitsBasic< unsigned short, 0, USHRT_MAX > {};

template<>
struct IntegerTraits< signed int > : Detail::IntegerTraitsBasic< signed int,INT_MIN, INT_MAX > {};

template<>
struct IntegerTraits< unsigned int > : Detail::IntegerTraitsBasic< unsigned int, 0, UINT_MAX > {};

template<>
struct IntegerTraits< signed long > : Detail::IntegerTraitsBasic< signed long, LONG_MIN, LONG_MAX > {};

template<>
struct IntegerTraits< unsigned long > : Detail::IntegerTraitsBasic< unsigned long, 0, ULONG_MAX > {};

template<>
struct IntegerTraits< signed long long > : Detail::IntegerTraitsBasic< signed long long, LLONG_MIN, LLONG_MAX > {};

template<>
struct IntegerTraits< unsigned long long > : Detail::IntegerTraitsBasic< unsigned long long, 0, ULLONG_MAX > {};

} // namespace TypeTraits

} // namespace BR


