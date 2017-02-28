/**
 * @file
 * @brief FloatingPointTraits
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/is_floating_point.hpp>
#include <libbr/type_traits/remove_const_volatile.hpp>

#if !defined(BR_GCC) && !defined(BR_CLANG)
#include <cfloat>
#endif

namespace BR {

inline namespace TypeTraits {

/**
 * @brief FloatingPointTraits
 * @tparam T
 */
template< typename T >
struct FloatingPointTraits;

} // namespace TypeTraits



namespace Detail {
namespace TypeTraits {

template< typename T >
struct FloatingPointTraitsBasic {
	using Type = T;
	static constexpr auto is_specialized = false;
	static constexpr SInt digits = 0;
	static constexpr SInt digits10 = 0;
	static constexpr SInt max_digits10 = 0;
	static constexpr SInt radix = 0;
	static constexpr SInt min_exponent = 0;
	static constexpr SInt max_exponent = 0;
	static constexpr SInt min_exponent10 = 0;
	static constexpr SInt max_exponent10 = 0;
	static constexpr auto min() noexcept -> Type { return T(); }
	static constexpr auto max() noexcept -> Type { return T(); }
	static constexpr auto lowest() noexcept -> Type { return T(); }
	static constexpr auto epsilon() noexcept -> Type { return T(); }
	static constexpr auto infinity() noexcept -> Type { return T(); }
};

constexpr auto get_max_digits10(SInt digits) -> SInt {
	return 2 + digits * 643 / 2136;
}

#if defined(BR_GCC) || defined(BR_CLANG)

template<>
struct FloatingPointTraitsBasic<float> {
	using Type = float;
	static constexpr auto is_specialized = true;
	static constexpr SInt digits = __FLT_MANT_DIG__;
	static constexpr SInt digits10 = __FLT_DIG__;
	static constexpr SInt max_digits10 = get_max_digits10(digits);
	static constexpr SInt radix = __FLT_RADIX__;
	static constexpr SInt min_exponent = __FLT_MIN_EXP__;
	static constexpr SInt max_exponent = __FLT_MAX_EXP__;
	static constexpr SInt min_exponent10 = __FLT_MIN_10_EXP__;
	static constexpr SInt max_exponent10 = __FLT_MAX_10_EXP__;
	static constexpr auto min() noexcept -> Type { return __FLT_MIN__; }
	static constexpr auto max() noexcept -> Type { return __FLT_MAX__; }
	static constexpr auto lowest() noexcept -> Type { return -max(); }
	static constexpr auto epsilon() noexcept -> Type { return __FLT_EPSILON__; }
	static constexpr auto infinity() noexcept -> Type { return __builtin_huge_valf(); }
};

template<>
struct FloatingPointTraitsBasic<double> {
	using Type = double;
	static constexpr auto is_specialized = true;
	static constexpr SInt digits = __DBL_MANT_DIG__;
	static constexpr SInt digits10 = __DBL_DIG__;
	static constexpr SInt max_digits10 = get_max_digits10(digits);
	static constexpr SInt radix = __FLT_RADIX__;
	static constexpr SInt min_exponent = __DBL_MIN_EXP__;
	static constexpr SInt max_exponent = __DBL_MAX_EXP__;
	static constexpr SInt min_exponent10 = __DBL_MIN_10_EXP__;
	static constexpr SInt max_exponent10 = __DBL_MAX_10_EXP__;
	static constexpr auto min() noexcept -> Type { return __DBL_MIN__; }
	static constexpr auto max() noexcept -> Type { return __DBL_MAX__; }
	static constexpr auto lowest() noexcept -> Type { return -max(); }
	static constexpr auto epsilon() noexcept -> Type { return __DBL_EPSILON__; }
	static constexpr auto infinity() noexcept -> Type { return __builtin_huge_val(); }
};

template<>
struct FloatingPointTraitsBasic<long double> {
	using Type = long double;
	static constexpr auto is_specialized = true;
	static constexpr SInt digits = __LDBL_MANT_DIG__;
	static constexpr SInt digits10 = __LDBL_DIG__;
	static constexpr SInt max_digits10 = get_max_digits10(digits);
	static constexpr SInt radix = __FLT_RADIX__;
	static constexpr SInt min_exponent = __LDBL_MIN_EXP__;
	static constexpr SInt max_exponent = __LDBL_MAX_EXP__;
	static constexpr SInt min_exponent10 = __LDBL_MIN_10_EXP__;
	static constexpr SInt max_exponent10 = __LDBL_MAX_10_EXP__;
	static constexpr auto min() noexcept -> Type { return __LDBL_MIN__; }
	static constexpr auto max() noexcept -> Type { return __LDBL_MAX__; }
	static constexpr auto lowest() noexcept -> Type { return -max(); }
	static constexpr auto epsilon() noexcept -> Type { return __LDBL_EPSILON__; }
	static constexpr auto infinity() noexcept -> Type { return __builtin_huge_vall(); }
};

#else

template<>
struct FloatingPointTraitsBasic<float> {
	using Type = float;
	static constexpr auto is_specialized = true;
	static constexpr SInt digits = FLT_MANT_DIG;
	static constexpr SInt digits10 = FLT_DIG;
	static constexpr SInt max_digits10 = get_max_digits10(digits);
	static constexpr SInt radix = FLT_RADIX;
	static constexpr SInt min_exponent = FLT_MIN_EXP;
	static constexpr SInt max_exponent = FLT_MAX_EXP;
	static constexpr SInt min_exponent10 = FLT_MIN_10_EXP;
	static constexpr SInt max_exponent10 = FLT_MAX_10_EXP;
	static constexpr auto min() noexcept -> Type { return FLT_MAX; }
	static constexpr auto max() noexcept -> Type { return FLT_MAX; }
	static constexpr auto lowest() noexcept -> Type { return -max(); }
	static constexpr auto epsilon() noexcept -> Type { return FLT_EPSILON; }
	static constexpr auto infinity() noexcept -> Type { return __builtin_huge_valf(); }
};

template<>
struct FloatingPointTraitsBasic<double> {
	using Type = double;
	static constexpr auto is_specialized = true;
	static constexpr SInt digits = DBL_MANT_DIG;
	static constexpr SInt digits10 = DBL_DIG;
	static constexpr SInt max_digits10 = get_max_digits10(digits);
	static constexpr SInt radix = FLT_RADIX;
	static constexpr SInt min_exponent = DBL_MIN_EXP;
	static constexpr SInt max_exponent = DBL_MAX_EXP;
	static constexpr SInt min_exponent10 = DBL_MIN_10_EXP;
	static constexpr SInt max_exponent10 = DBL_MAX_10_EXP;
	static constexpr auto min() noexcept -> Type { return DBL_MIN; }
	static constexpr auto max() noexcept -> Type { return DBL_MAX; }
	static constexpr auto lowest() noexcept -> Type { return -max(); }
	static constexpr auto epsilon() noexcept -> Type { return DBL_EPSILON; }
	static constexpr auto infinity() noexcept -> Type { return __builtin_huge_val(); }
};

template<>
struct FloatingPointTraitsBasic<long double> {
	using Type = long double;
	static constexpr auto is_specialized = true;
	static constexpr SInt digits = LDBL_MANT_DIG;
	static constexpr SInt digits10 = LDBL_DIG;
	static constexpr SInt max_digits10 = get_max_digits10(digits);
	static constexpr SInt radix = FLT_RADIX;
	static constexpr SInt min_exponent = LDBL_MIN_EXP;
	static constexpr SInt max_exponent = LDBL_MAX_EXP;
	static constexpr SInt min_exponent10 = LDBL_MIN_10_EXP;
	static constexpr SInt max_exponent10 = LDBL_MAX_10_EXP;
	static constexpr auto min() noexcept -> Type { return LDBL_MIN; }
	static constexpr auto max() noexcept -> Type { return LDBL_MAX; }
	static constexpr auto lowest() noexcept -> Type { return -LDBL_MAX; }
	static constexpr auto epsilon() noexcept -> Type { return LDBL_EPSILON; }
	static constexpr auto infinity() noexcept -> Type { return __builtin_huge_vall(); }
};

#endif

template< typename T >
using FloatingPointTraits = FloatingPointTraitsBasic< RemoveConstVolatile<T> >;

} // namespace TypeTraits
} // namespace Detail

inline namespace TypeTraits {

template< typename T >
struct FloatingPointTraits : public Detail::TypeTraits::FloatingPointTraits<T> {
};

} // namespace TypeTraits

} // namespace BR


