/**
 * @file
 * @brief float
 * @author Bromine0x23
 * @since 2015/11/2
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/sign.hpp>

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

constexpr auto infinity32() -> Float32;

constexpr auto infinity64() -> Float64;

constexpr auto nan32() -> Float32;

constexpr auto nan64() -> Float64;

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

constexpr auto to_raw(Float32 f) -> UInt32 {
	return *reinterpret_cast<UInt32 *>(&f);
}

constexpr auto to_raw(Float64 f) -> UInt64 {
	return *reinterpret_cast<UInt64 *>(&f);
}

constexpr auto to_float32(UInt32 u) -> Float32 {
	return *reinterpret_cast<Float32 *>(&u);
}

constexpr auto to_float64(UInt64 u) -> Float64 {
	return *reinterpret_cast<Float64 *>(&u);
}

constexpr auto get_high_part(Float64 f) -> UInt32 {
	return UInt32(to_raw(f) >> 32);
}

constexpr auto get_low_part(Float64 f) -> UInt32 {
	return to_raw(f) & 0xFFFFFFFFU;
}

constexpr auto to_float64(UInt32 h, UInt32 l) -> Float64 {
	return to_float64((UInt64(h) << 32) | l);
}

} // namespace Math
} // namespace Detail

constexpr auto infinity32() -> Float32 {
	return Detail::Math::to_float32(0x7F800000U);
}

constexpr auto infinity64() -> Float64 {
	return Detail::Math::to_float64(0x7FF00000U, 0x00000000U);
}

constexpr auto nan32() -> Float32 {
	return Detail::Math::to_float32(0x7FFFFFFFU);
}

constexpr auto nan64() -> Float64 {
	return Detail::Math::to_float64(0x7FFFFFFFU, 0xFFFFFFFFU);
}

constexpr auto sign(Float32 f) -> Sign {
	return (Detail::Math::to_raw(f) & 0x80000000U) == 0 ? Sign::POS : Sign::NEG;
};

constexpr auto sign(Float64 f) -> Sign {
	return (Detail::Math::get_high_part(f) & 0x80000000U) == 0 ? Sign::POS : Sign::NEG;
};

constexpr auto abs(Float32 f) -> Float32 {
	return Detail::Math::to_float32(Detail::Math::to_raw(f) & 0x7FFFFFFFU);
};

constexpr auto abs(Float64 f) -> Float64 {
	return Detail::Math::to_float64(Detail::Math::get_high_part(f) & 0x7FFFFFFFU, Detail::Math::get_low_part(f));
};

BR_CONSTEXPR_AFTER_CXX11 inline auto classify(Float32 f) -> FloatCategory {
	UInt32 r = Detail::Math::to_raw(f) & 0x7FFFFFFFU;
	if (r == 0) {
		return FloatCategory::zero;
	} else if (r < 0x00800000U) {
		return FloatCategory::subnormal;
	} else if (r >= 0x7F800000U) {
		return r > 0x7F800000 ? FloatCategory::nan : FloatCategory::infinite;
	}
	return FloatCategory::normal;
}

BR_CONSTEXPR_AFTER_CXX11 inline auto classify(Float64 f) -> FloatCategory {
	UInt32 h = Detail::Math::get_high_part(f);
	UInt32 l = Detail::Math::get_low_part(f);
	l |= h & 0x000FFFFF;
	h &= 0x7FF00000;
	if ((h | l) == 0) {
		return FloatCategory::zero;
	} else if (h == 0) {
		return FloatCategory::subnormal;
	} else if (h == 0x7FF00000U) {
		return l != 0 ? FloatCategory::nan : FloatCategory::infinite;
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
	return (UInt32(0x7F800000U - (Detail::Math::to_raw(f) & 0x7FFFFFFFU)) >> 31) != 0;
}

constexpr auto is_nan(Float64 f) -> bool {
	return ((0x7FF00000U - (Detail::Math::get_high_part(f) & 0x7FFFFFFFU) | (Detail::Math::get_low_part(f) != 0)) >> 31) != 0;
}

} // namespace BR