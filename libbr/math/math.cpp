#include <libbr/math/complex.hpp>
#include <libbr/math/float.hpp>

namespace BR {

// template class Complex<SFloat>;
// template class Complex<DFloat>;
// template class Complex<QFloat>;

// template class Complex<DFloat>;

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
	SInt32 raw = Detail::Math::to_raw(f);
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
	return Detail::Math::to_float32(raw);
}

auto ceil(Float64 f) -> Float64 {
	SInt32 high = Detail::Math::get_high_part(f);
	UInt32 low = Detail::Math::get_low_part(f);
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
	return Detail::Math::to_float64(high, low);
}

auto floor(Float32 f) -> Float32 {
	SInt32 raw = Detail::Math::to_raw(f);
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
	return Detail::Math::to_float32(raw);
}

auto floor(Float64 f) -> Float64 {
	SInt32 high = Detail::Math::get_high_part(f);
	UInt32 low = Detail::Math::get_low_part(f);
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
	return Detail::Math::to_float64(high, low);
}

auto truncate(Float32 f) -> Float32 {
	SInt32 raw = Detail::Math::to_raw(f);
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
	return Detail::Math::to_float32(raw);
}

auto truncate(Float64 f) -> Float64 {
	SInt32 high = Detail::Math::get_high_part(f);
	UInt32 low = Detail::Math::get_low_part(f);
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
	return Detail::Math::to_float64(high, low);
}

auto round(Float32 f) -> Float32 {
	SInt32 raw = Detail::Math::to_raw(f);
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
	return Detail::Math::to_float32(raw);
}

auto round(Float64 f) -> Float64 {
	SInt32 high = Detail::Math::get_high_part(f);
	UInt32 low = Detail::Math::get_low_part(f);
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
	return Detail::Math::to_float64(high, low);
}

} // namespace BR

