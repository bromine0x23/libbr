#include <libbr/math/complex.hpp>
#include <libbr/math/float.hpp>
#include <libbr/math/copy_sign.hpp>
#include <libbr/math/is_finite.hpp>
#include <libbr/math/is_infinite.hpp>
#include <libbr/math/is_nan.hpp>
#include <libbr/math/is_normal.hpp>
#include <cmath>

auto libbr_copy_sign_s(BR::SFloat x, BR::SFloat y) -> BR::SFloat {
	return std::copysign(x, y);
}

auto libbr_copy_sign_d(BR::DFloat x, BR::DFloat y) -> BR::DFloat {
	return std::copysign(x, y);
}

auto libbr_copy_sign_q(BR::QFloat x, BR::QFloat y) -> BR::QFloat {
	return std::copysign(x, y);
}

#if !defined(BR_GCC)
auto libbr_is_finite_s(BR::SFloat x) -> bool {
	return std::isfinite(x);
}

auto libbr_is_finite_d(BR::DFloat x) -> bool {
	return std::isfinite(x);
}

auto libbr_is_finite_q(BR::QFloat x) -> bool {
	return std::isfinite(x);
}
#endif

auto libbr_is_infinite_s(BR::SFloat x) -> bool {
	return std::isinf(x);
}

auto libbr_is_infinite_d(BR::DFloat x) -> bool {
	return std::isinf(x);
}

auto libbr_is_infinite_q(BR::QFloat x) -> bool {
	return std::isinf(x);
}

auto libbr_is_nan_s(BR::SFloat x) -> bool {
	return std::isnan(x);
}

auto libbr_is_nan_d(BR::DFloat x) -> bool {
	return std::isnan(x);
}

auto libbr_is_nan_q(BR::QFloat x) -> bool {
	return std::isnan(x);
}

auto libbr_is_normal_s(BR::SFloat x) -> bool {
	return std::isnormal(x);
}

auto libbr_is_normal_d(BR::DFloat x) -> bool {
	return std::isnormal(x);
}

auto libbr_is_normal_q(BR::QFloat x) -> bool {
	return std::isnormal(x);
}

namespace BR {

template auto Complex<SFloat>::operator*(Complex const & y) const -> Complex;
template auto Complex<SFloat>::operator/(Complex const & y) const -> Complex;
template auto Complex<DFloat>::operator*(Complex const & y) const -> Complex;
template auto Complex<DFloat>::operator/(Complex const & y) const -> Complex;
template auto Complex<QFloat>::operator*(Complex const & y) const -> Complex;
template auto Complex<QFloat>::operator/(Complex const & y) const -> Complex;

namespace {

static constexpr auto get_exponent32(SInt32 raw) -> SInt32 {
	return SInt32((raw >> 23) & 0xFFU) - 0x7F;
}

static constexpr auto get_exponent64(SInt32 high) -> SInt32 {
	return SInt32((high >> 20) & 0x7FFU) - 0x3FF;
}

}

auto ceil(Float32 f) -> Float32 {
	SInt32 raw = Detail::Float::to_raw(f);
	SInt32 const exp = get_exponent32(raw);

	if (exp < 0) { // |f| < 1
		if (raw < 0) { // f < 0
			// f <- -0.0
			raw = 0x80000000;
		} else if (raw != 0) { // f != +0.0
			// f <- +1.0s
			raw = 0x3F800000;
		}
	} else if (exp < 23) {
		auto const mask = 0x007FFFFFU >> exp;
		if ((raw & mask) == 0) { // f is integral
			return f;
		}
		if (raw > 0) {
			raw += SInt32(0x00800000) >> exp;
		}
		raw &= ~mask;
	} else if (exp < 0x80) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return Detail::Float::to_float32(raw);
}

auto ceil(Float64 f) -> Float64 {
	SInt32 high = Detail::Float::get_high_part(f);
	UInt32 low = Detail::Float::get_low_part(f);
	SInt32 const exp = get_exponent64(high);

	if (exp < 0) { // |f| < 1
		if (high < 0) { // f < 0
			// f <- -0.0
			high = 0x80000000;
			low = 0x00000000U;
		} else if ((high | low) != 0) { // f != +0.0
			// f <- +1.0
			high = 0x3FF00000;
			low = 0x00000000U;
		}
	} else if (exp < 20) {
		auto const mask = 0x000FFFFFU >> exp;
		if (((high & mask) | low) == 0) { // f is integral
			return f;
		}
		if (high > 0) { // f > 0
			high += SInt32(0x00100000) >> exp;
		}
		high &= ~mask;
		low = 0x00000000U;
	} else if (exp < 52) {
		auto const mask = 0xFFFFFFFFU >> (exp - 20);
		if ((low & mask) == 0) { // f is integral
			return f;
		}
		if (high > 0) { // f > 0
			if (exp == 20) {
				++high;
			} else {
				UInt32 x = low + (1 << (52 - exp));
				if (x < low) {
					++high;
				}
				low = x;
			}
		}
		low &= ~mask;
	} else if (exp < 0x400) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return Detail::Float::to_float64(high, low);
}

auto floor(Float32 f) -> Float32 {
	SInt32 raw = Detail::Float::to_raw(f);
	SInt32 const exp = get_exponent32(raw);

	if (exp < 0) { // |f| < 1
		if (raw > 0) { // f > 0
			// f <- +0.0
			raw = 0x00000000;
		} else if ((raw & 0x7FFFFFFFU) != 0) { // f != -0.0
			// f <- -1.0
			raw = 0xBF800000;
		}
	} else if (exp < 23) {
		auto const mask = 0x007FFFFFU >> exp;
		if ((raw & mask) == 0) { // f is integral
			return f;
		}
		if (raw < 0) {
			raw += SInt32(0x00800000U) >> exp;
		}
		raw &= ~mask;
	} else if (exp < 0x80) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return Detail::Float::to_float32(raw);
}

auto floor(Float64 f) -> Float64 {
	SInt32 high = Detail::Float::get_high_part(f);
	UInt32 low = Detail::Float::get_low_part(f);
	SInt32 const exp = get_exponent64(high);
	if (exp < 0) {
		if (high > 0) { // f > 0
			// f <- +0.0
			high = 0x00000000;
			low = 0x00000000U;
		} else if (((high & 0x7FFFFFFFU) | low) != 0) {
			// f <- -1.0
			high = 0xBFF00000;
			low = 0x00000000U;
		}
	} else if (exp < 20) {
		auto const mask = 0x000FFFFFU >> exp;
		if (((high & mask) | low) == 0) { // f is integral
			return f;
		}
		if (high < 0) { // f < 0
			high += SInt32(0x00100000) >> exp;
		}
		high &= ~mask;
		low = 0;
	} else if (exp < 52) {
		auto const mask = 0xFFFFFFFFU >> (exp - 20);
		if ((low & mask) == 0) { // f is integral
			return f;
		}
		if (high < 0) { // f < 0
			if (exp == 20) {
				++high;
			} else {
				UInt32 x = low + (1 << (52 - exp));
				if (x < low) {
					++high;
				}
				low = x;
			}
		}
		low &= ~mask;
	} else if (exp < 0x400) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return Detail::Float::to_float64(high, low);
}

auto truncate(Float32 f) -> Float32 {
	SInt32 raw = Detail::Float::to_raw(f);
	SInt32 const exp = get_exponent32(raw);
	if (exp < 0) { // |f| < 1
		raw &= 0x80000000;
	} else if (exp < 23) {
		raw = (raw & 0x80000000) | (raw & ~(0x007FFFFFU >> exp));
	} else if (exp < 0x80) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return Detail::Float::to_float32(raw);
}

auto truncate(Float64 f) -> Float64 {
	SInt32 high = Detail::Float::get_high_part(f);
	UInt32 low = Detail::Float::get_low_part(f);
	SInt32 const exp = get_exponent64(high);
	if (exp < 0) { // |f| < 1
		high &= 0x80000000;
		low = 0x00000000U;
	} else if (exp < 20) {
		high = (high & 0x80000000) | (high & ~(0x000FFFFFU >> exp));
		low = 0x00000000U;
	} else if (exp < 52) {
		low &= ~0xFFFFFFFFU > (exp - 20);
	} else if (exp < 0x400) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return Detail::Float::to_float64(high, low);
}

auto round(Float32 f) -> Float32 {
	SInt32 raw = Detail::Float::to_raw(f);
	SInt32 const exp = get_exponent32(raw);
	if (exp < 0) { // |f| < 1
		raw &= 0x80000000;
		if (exp == -1) {
			raw |= 0x3F800000;
		}
	} else if (exp < 23) {
		auto const mask = 0x007FFFFFU >> exp;
		if ((raw & mask) == 0) { // f is integral
			return f;
		}
		raw += 0x00400000 >> exp;
		raw &= ~mask;
	} else if (exp < 0x80) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return Detail::Float::to_float32(raw);
}

auto round(Float64 f) -> Float64 {
	SInt32 high = Detail::Float::get_high_part(f);
	UInt32 low = Detail::Float::get_low_part(f);
	SInt32 const exp = get_exponent64(high);
	if (exp < 0) { // |f| < 1
		high &= 0x80000000;
		if (exp == -1) {
			high |= 0x3FF00000;
		}
		low = 0x00000000U;
	} else if (exp < 20) {
		auto const mask = 0x000FFFFFU >> exp;
		if (((high & mask) | low) == 0) { // f is integral
			return f;
		}
		high += 0x00080000 >> exp;
		high &= ~mask;
		low = 0x00000000U;
	} else if (exp < 52) {
		auto const mask = 0xFFFFFFFFU >> (exp - 20);
		if ((low & mask) == 0) { // f is integral
			return f;
		}
		auto x = low + (1 << (51 - exp));
		if (x < low) {
			++high;
		}
		low = x;
		low &= ~mask;
	} else if (exp < 0x400) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return Detail::Float::to_float64(high, low);
}

} // namespace BR

