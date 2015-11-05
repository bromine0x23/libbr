/**
 * @file
 * @brief float
 * @author Bromine0x23
 * @since 2015/11/2
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/sign.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

using Float32 = float;

using Float64 = double;

enum class FloatCategory {
	infinite,
	nan,
	zero,
	subnormal,
	normal,
};

template< typename TFloat >
struct FloatConstants {

	/**
	 * @brief 1/2
	 */
	constexpr static TFloat half = 0.5000000000000000000000000000000000000000E+00L;

	/**
	 * @brief 1/3
	 */
	constexpr static TFloat third = 0.3333333333333333333333333333333333333333E+00L;

	/**
	 * @brief 2/3
	 */
	constexpr static TFloat two_thirds = 0.6666666666666666666666666666666666666667E+00L;

	/**
	 * @brief 1/4
	 */
	constexpr static TFloat quarter = 0.2500000000000000000000000000000000000000E+00L;

	/**
	 * @brief 3/4
	 */
	constexpr static TFloat three_quarters = 0.7500000000000000000000000000000000000000E+00L;

	/**
	 * @brief 2^-2
	 */
	constexpr static TFloat root_two = 0.1414213562373095048801688724209698078569E+01L;

	/**
	 * @brief 2^-2 / 2 == 1 / 2^-2
	 */
	constexpr static TFloat half_root_two = 0.7071067811865475244008443621048490392848E+00L;

	/**
	 * @brief 3^-2
	 */
	constexpr static TFloat root_three = 0.1732050807568877293527446341505872366942E+01L;

	/**
	 * @brief e
	 */
	constexpr static TFloat e = 0.2718281828459045235360287471352662497757E+01L;

	/**
	 * @brief e^-2
	 */
	constexpr static TFloat root_e = 0.1648721270700128146848650787814163571653E+01L;

	/**
	 * @brief log_e(2)
	 */
	constexpr static TFloat ln_two = 0.6931471805599453094172321214581765680755E+00L;

	/**
	 * @brief log_2(e) == 1 / log_e(2)
	 */
	constexpr static TFloat lb_e = 0.1442695040888963407359924681001892137426E+01L;

	/**
	 * @brief log_e(log_e(2))
	 */
	constexpr static TFloat ln_ln_two = -0.3665129205816643270124391582326694694542E+00L;

	/**
	 * @brief log_e(10)
	 */
	constexpr static TFloat ln_ten = 0.2302585092994045684017991454684364207601E+01L;

	/**
	 * @brief log_10(e) == 1 / log_e(10)
	 */
	constexpr static TFloat lg_e = 0.4342944819032518276511289189166050822943E+00L;

	/**
	 * @brief π
	 */
	constexpr static TFloat pi = 0.3141592653589793238462643383279502884197E+01L;

	/**
	 * @brief π / 2
	 */
	constexpr static TFloat half_pi = 0.1570796326794896619231321691639751442098E+01L;

	/**
	 * @brief π / 3
	 */
	constexpr static TFloat third_pi = 0.1047197551196597746154214461093167628065E+01L;

	/**
	 * @brief 1 / π
	 */
	constexpr static TFloat one_div_pi = 0.3183098861837906715377675267450287240689E+00L;

	/**
	 * @brief 2 / π
	 */
	constexpr static TFloat two_div_pi = 0.6366197723675813430755350534900574481378E+00L;

	/**
	 * @brief π^-2
	 */
	constexpr static TFloat root_pi = 0.1772453850905516027298167483341145182797E+01L;

	/**
	 * @brief (π / 2)^-2
	 */
	constexpr static TFloat root_half_pi = 0.1253314137315500251207882642405522626503E+01L;

	/**
	 * @brief (2π)^-2
	 */
	constexpr static TFloat root_two_pi = 0.2506628274631000502415765284811045253006E+01L;

	/**
	 * @brief π^2
	 */
	constexpr static TFloat pi_sqr = 0.9869604401089358618834490999876151135313E+01L;

	/**
	 * @brief π^2 / 6 = ∑1/(n^2)
	 */
	constexpr static TFloat pi_sqr_div_six = 0.1644934066848226436472415166646025189218E+01L;

	/**
	 * @brief sin(1)
	 */
	constexpr static TFloat sin_one = 0.8414709848078965066525023216302989996225E+00L;

	/**
	 * @brief cos(1)
	 */
	constexpr static TFloat cos_one = 0.5403023058681397174009366074429766037323E+00L;

	/**
	 * @brief φ
	 */
	constexpr static TFloat phi = 0.1618033988749894848204586834365638117720E+01L;

};

constexpr auto infinity32() -> Float32;

constexpr auto infinity32(Sign sign) -> Float32;

constexpr auto infinity64() -> Float64;

constexpr auto infinity64(Sign sign) -> Float32;

constexpr auto infinity(TypeWrapper<Float32> _dummy) -> Float32;

constexpr auto infinity(TypeWrapper<Float64> _dummy) -> Float64;

constexpr auto nan32() -> Float32;

constexpr auto nan64() -> Float64;

constexpr auto nan(TypeWrapper<Float32> _dummy) -> Float32;

constexpr auto nan(TypeWrapper<Float64> _dummy) -> Float64;

constexpr auto sign(Float32 f) -> Sign;

constexpr auto sign(Float64 f) -> Sign;

constexpr auto abs(Float32 f) -> Float32;

constexpr auto abs(Float64 f) -> Float64;

BR_CONSTEXPR_AFTER_CXX11 auto classify(Float32 f) -> FloatCategory;

BR_CONSTEXPR_AFTER_CXX11 auto classify(Float64 f) -> FloatCategory;

BR_CONSTEXPR_AFTER_CXX11 auto is_normal(Float32 f) -> bool;

BR_CONSTEXPR_AFTER_CXX11 auto is_normal(Float64 f) -> bool;

constexpr auto is_finite(Float32 f) -> bool;

constexpr auto is_finite(Float64 f) -> bool;

constexpr auto is_infinite(Float32 f) -> bool;

constexpr auto is_infinite(Float64 f) -> bool;

constexpr auto is_nan(Float32 f) -> bool;

constexpr auto is_nan(Float64 f) -> bool;

constexpr auto copy_sign(Float32 x, Float32 y) -> Float32;

constexpr auto copy_sign(Float64 x, Float64 y) -> Float64;

auto ceil(Float32 f) -> Float32;

auto ceil(Float64 f) -> Float64;

auto floor(Float32 f) -> Float32;

auto floor(Float64 f) -> Float64;

auto truncate(Float32 f) -> Float32;

auto truncate(Float64 f) -> Float64;

auto round(Float32 f) -> Float32;

auto round(Float64 f) -> Float64;

namespace Detail {
namespace Math {

constexpr auto to_raw(Float32 f) -> SInt32 {
	return *reinterpret_cast<SInt32 *>(&f);
}

constexpr auto to_raw(Float64 f) -> SInt64 {
	return *reinterpret_cast<SInt64 *>(&f);
}

constexpr auto to_float32(SInt32 u) -> Float32 {
	return *reinterpret_cast<Float32 *>(&u);
}

constexpr auto to_float64(SInt64 u) -> Float64 {
	return *reinterpret_cast<Float64 *>(&u);
}

constexpr auto get_high_part(Float64 f) -> SInt32 {
	return SInt32(to_raw(f) >> 32);
}

constexpr auto get_low_part(Float64 f) -> UInt32 {
	return to_raw(f) & 0xFFFFFFFFU;
}

constexpr auto to_float64(SInt32 h, UInt32 l) -> Float64 {
	return to_float64((SInt64(h) << 32) | l);
}

} // namespace Math
} // namespace Detail

constexpr auto infinity32() -> Float32 {
	return Detail::Math::to_float32(0x7F800000);
}

constexpr auto infinity32(Sign sign) -> Float32 {
	return sign == Sign::POS ? Detail::Math::to_float32(0x7F800000) : Detail::Math::to_float32(0xFF800000);
}

constexpr auto infinity64() -> Float64 {
	return Detail::Math::to_float64(0x7FF0000000000000LL);
}

constexpr auto infinity64(Sign sign) -> Float32 {
	return sign == Sign::POS ? Detail::Math::to_float64(0x7FF0000000000000LL) : Detail::Math::to_float64(0xFFF0000000000000LL);
}

constexpr auto infinity(TypeWrapper<Float32> _dummy) -> Float32 {
	return infinity32();
}

constexpr auto infinity(TypeWrapper<Float64> _dummy) -> Float64 {
	return infinity64();
}

constexpr auto nan32() -> Float32 {
	return Detail::Math::to_float32(0x7FFFFFFF);
}

constexpr auto nan64() -> Float64 {
	return Detail::Math::to_float64(0x7FFFFFFFFFFFFFFFLL);
}

constexpr auto nan(TypeWrapper<Float32> _dummy) -> Float32 {
	return nan32();
}

constexpr auto nan(TypeWrapper<Float64> _dummy) -> Float64 {
	return nan64();
}

constexpr auto sign(Float32 f) -> Sign {
	return Detail::Math::to_raw(f) > 0 ? Sign::POS : Sign::NEG;
};

constexpr auto sign(Float64 f) -> Sign {
	return Detail::Math::get_high_part(f) > 0 ? Sign::POS : Sign::NEG;
};

constexpr auto abs(Float32 f) -> Float32 {
	return Detail::Math::to_float32(Detail::Math::to_raw(f) & 0x7FFFFFFF);
};

constexpr auto abs(Float64 f) -> Float64 {
	return Detail::Math::to_float64(Detail::Math::get_high_part(f) & 0x7FFFFFFF, Detail::Math::get_low_part(f));
};

BR_CONSTEXPR_AFTER_CXX11 inline auto classify(Float32 f) -> FloatCategory {
	FloatCategory category = FloatCategory::normal;
	UInt32 r = Detail::Math::to_raw(f) & 0x7FFFFFFFU;
	if (r == 0x00000000U) {
		category = FloatCategory::zero;
	} else if (r < 0x00800000U) {
		category = FloatCategory::subnormal;
	} else if (r == 0x7F800000U) {
		category = FloatCategory::infinite;
	} else if (r > 0x7F800000U) {
		category = FloatCategory::nan;
	}
	return category;
}

BR_CONSTEXPR_AFTER_CXX11 inline auto classify(Float64 f) -> FloatCategory {
	FloatCategory category = FloatCategory::normal;
	SInt32 high = Detail::Math::get_high_part(f);
	UInt32 low = Detail::Math::get_low_part(f);
	UInt32 t = low | high & 0x000FFFFF;
	UInt32 u = high & 0x7FF00000U;
	if ((t | u) == 0x00000000U) {
		category = FloatCategory::zero;
	} else if (u == 0x00000000U) {
		category = FloatCategory::subnormal;
	} else if (u == 0x7FF00000U) {
		category = (t != 0x00000000U ? FloatCategory::nan : FloatCategory::infinite);
	}
	return FloatCategory::normal;
}

BR_CONSTEXPR_AFTER_CXX11 inline auto is_normal(Float32 f) -> bool {
	return classify(f) == FloatCategory::normal;
}

BR_CONSTEXPR_AFTER_CXX11 inline auto is_normal(Float64 f) -> bool {
	return classify(f) == FloatCategory::normal;
}

constexpr auto is_finite(Float32 f) -> bool {
	return (((Detail::Math::to_raw(f) & 0x7FFFFFFFU) - 0x7F800000U) >> 31) != 0;
}

constexpr auto is_finite(Float64 f) -> bool {
	return (((Detail::Math::get_high_part(f) & 0x7FFFFFFFU) - 0x7FF00000U) >> 31) != 0;
}

constexpr auto is_infinite(Float32 f) -> bool {
	return ((Detail::Math::to_raw(f) & 0x7FFFFFFFU) ^ 0x7F800000U) == 0;
}

constexpr auto is_infinite(Float64 f) -> bool {
	return (Detail::Math::get_low_part(f) | (Detail::Math::get_high_part(f) & 0x7FFFFFFFU) ^ 0x7FF00000U) == 0;
}

constexpr auto is_nan(Float32 f) -> bool {
	return ((0x7F800000U - (Detail::Math::to_raw(f) & 0x7FFFFFFFU)) >> 31) != 0;
}

constexpr auto is_nan(Float64 f) -> bool {
	return ((0x7FF00000U - (Detail::Math::get_high_part(f) & 0x7FFFFFFFU) | (Detail::Math::get_low_part(f) != 0)) >> 31) != 0;
}

constexpr auto copy_sign(Float32 x, Float32 y) -> Float32 {
	return Detail::Math::to_float32((Detail::Math::to_raw(x) & 0x7FFFFFFF) | (Detail::Math::to_raw(y) & 0x80000000));
}

constexpr auto copy_sign(Float64 x, Float64 y) -> Float64 {
	return Detail::Math::to_float64((Detail::Math::get_high_part(x) & 0x7FFFFFFF) | (Detail::Math::get_high_part(y) & 0x80000000), Detail::Math::get_low_part(x));
}

} // namespace BR