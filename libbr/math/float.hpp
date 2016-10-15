/**
 * @file
 * @brief float
 * @author Bromine0x23
 * @since 2015/11/2
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/sign.hpp>
#include <libbr/math/float_constants.hpp>
#include <libbr/math/is_finite.hpp>
#include <libbr/math/is_infinite.hpp>
#include <libbr/math/is_nan.hpp>
#include <libbr/math/is_normal.hpp>
#include <libbr/math/detail/float.hpp>
#include <libbr/type_operate/type.hpp>

namespace BR {

enum class FloatCategory {
	infinite,
	nan,
	zero,
	subnormal,
	normal,
};

constexpr auto infinity32() -> Float32;

constexpr auto infinity32(Sign sign) -> Float32;

constexpr auto infinity64() -> Float64;

constexpr auto infinity64(Sign sign) -> Float64;

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

auto ceil(Float32 f) -> Float32;

auto ceil(Float64 f) -> Float64;

auto floor(Float32 f) -> Float32;

auto floor(Float64 f) -> Float64;

auto truncate(Float32 f) -> Float32;

auto truncate(Float64 f) -> Float64;

auto round(Float32 f) -> Float32;

auto round(Float64 f) -> Float64;

constexpr auto infinity32() -> Float32 {
	return Detail::Float::to_float32(0x7F800000);
}

constexpr auto infinity32(Sign sign) -> Float32 {
	return sign == Sign::POS ? Detail::Float::to_float32(0x7F800000) : Detail::Float::to_float32(0xFF800000);
}

constexpr auto infinity64() -> Float64 {
	return Detail::Float::to_float64(0x7FF0000000000000LL);
}

constexpr auto infinity64(Sign sign) -> Float64 {
	return sign == Sign::POS ? Detail::Float::to_float64(0x7FF0000000000000LL) : Detail::Float::to_float64(0xFFF0000000000000LL);
}

constexpr auto infinity(TypeWrapper<Float32> _dummy) -> Float32 {
	return infinity32();
}

constexpr auto infinity(TypeWrapper<Float64> _dummy) -> Float64 {
	return infinity64();
}

constexpr auto nan32() -> Float32 {
	return Detail::Float::to_float32(0x7FFFFFFF);
}

constexpr auto nan64() -> Float64 {
	return Detail::Float::to_float64(0x7FFFFFFFFFFFFFFFLL);
}

constexpr auto nan(TypeWrapper<Float32> _dummy) -> Float32 {
	return nan32();
}

constexpr auto nan(TypeWrapper<Float64> _dummy) -> Float64 {
	return nan64();
}

constexpr auto sign(Float32 f) -> Sign {
	return Detail::Float::to_raw(f) > 0 ? Sign::POS : Sign::NEG;
};

constexpr auto sign(Float64 f) -> Sign {
	return Detail::Float::get_high_part(f) > 0 ? Sign::POS : Sign::NEG;
};

constexpr auto abs(Float32 f) -> Float32 {
	return Detail::Float::to_float32(Detail::Float::to_raw(f) & 0x7FFFFFFF);
};

constexpr auto abs(Float64 f) -> Float64 {
	return Detail::Float::to_float64(Detail::Float::get_high_part(f) & 0x7FFFFFFF, Detail::Float::get_low_part(f));
};

BR_CONSTEXPR_AFTER_CXX11 inline auto classify(Float32 f) -> FloatCategory {
	FloatCategory category = FloatCategory::normal;
	UInt32 r = Detail::Float::to_raw(f) & 0x7FFFFFFFU;
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
	SInt32 high = Detail::Float::get_high_part(f);
	UInt32 low = Detail::Float::get_low_part(f);
	UInt32 t = low | (high & 0x000FFFFFU);
	UInt32 u = high & 0x7FF00000U;
	if ((t | u) == 0x00000000U) {
		category = FloatCategory::zero;
	} else if (u == 0x00000000U) {
		category = FloatCategory::subnormal;
	} else if (u == 0x7FF00000U) {
		category = (t != 0x00000000U ? FloatCategory::nan : FloatCategory::infinite);
	}
	return category;
}

} // namespace BR