#include <libbr/math/detail/bind.hpp>
#include <libbr/math/complex.hpp>
#include <libbr/math/float.hpp>
#include <cmath>
#include <cfloat>

using namespace BR;

#include <libbr/math/function/detail/exp2.inl>

auto libbr_exp2_32(Float32 x) -> Float32 {
	static constexpr Float32 HMARK = FLT_MAX_EXP;
	static constexpr Float32 LMARK = FLT_MIN_EXP - FLT_MANT_DIG - 1;
	static Float32 const THREE_TWO_P14 = Detail::Math::Bind32(0x47400000U).f; // 3 * 2^14

	if (is_less(x, HMARK)) {
		if (!is_greater(x, LMARK)) {
			return 0;
		}
	} else {
		return Detail::Math::Bind32(0x7F000000U).f * x; // x * 2 ^ +127
	}

	// x = ex + t / 512 + r, -128 <= t < 128, -1/512 <= r <= 1/512

	// mx = ex + t / 256
	Float32 mx = x + THREE_TWO_P14;
	mx -= THREE_TWO_P14;

	// r
	Float32 r = x - mx;

	// i = (ex * 256 + t) + 128 = mx * 256 + 128
	auto i = SInt(mx * 256.0F + 128.0F);

	// x = ex + t / 256 + e + d, -7E-4 < e < 7E-4, 2^(t / 256 + e) === 2^-64

	Float32 d = r - Detail::Math::Bind32(EXP2_32_DELTA[i & 0xFF]).f;

	// sx = 2^(t/255 + e + ex)
	auto sx = Detail::Math::Bind32(EXP2_32_ACCURATE[i & 0xFF]);

	i >>= 8;

	bool unsafe = abs(i) >= 124U;
	sx.exponent += i >> unsafe;

	Float32 ux = (.24022656679F * d + .69314736128F) * sx.f;

	Float32 result = ux * d + sx.f;
	if (!unsafe) {
		return result;
	} else {
		auto scale = Detail::Math::Bind32(1.0F);
		scale.exponent += i - (i >> unsafe);
		return result * scale.f;
	}
}

auto libbr_exp2_64(Float64 x) -> Float64 {
	static constexpr Float64 HMARK = DBL_MAX_EXP;
	static constexpr Float64 LMARK = DBL_MIN_EXP - DBL_MANT_DIG - 1;
	static Float64 const THREE_TWO_P42 = Detail::Math::Bind64(0x42A80000U, 0U).f;

	if (is_less(x, HMARK)) {
		if (!is_greater(x, LMARK)) {
			return 0;
		}
	} else {
		return Detail::Math::Bind64(0x7FE00000U, 0U).f * x; // x * 2 ^ +127
	}

	// x = ex + t / 512 + r, -256 <= t < 256, -1/1024 <= r <= 1/1024

	// mx = ex + t / 256
	Float64 mx = x + THREE_TWO_P42;
	mx -= THREE_TWO_P42;

	// r
	Float64 r = x - mx;

	// i = (ex * 512 + t) + 256 = mx * 512 + 256
	auto i = SInt(mx * 512.0 + 256.0);

	// x = ex + t / 256 + e + d, -7E-4 < e < 7E-4, 2^(t / 256 + e) === 2^-64
	Float64 d = r - Detail::Math::Bind64(EXP2_64_DELTA[i & 0x1FF], 0U).f;

	// sx = 2^(t/512 + e + ex)
	auto sx = Detail::Math::Bind64(EXP2_64_ACCURATE[i & 0x1FF]);

	i >>= 9;

	bool unsafe = abs(i) >= -DBL_MIN_EXP - 1;
	sx.exponent += i >> unsafe;

	// ux = 2^d - 1
	Float64 ux = (((.0096181293647031180 * x + .055504110254308625) * d + .240226506959100583) * x + .69314718055994495) * sx.f;

	// f = (2^d - 1) * 2^(t/512 + e + ex) + 2^(t/512 + e + ex)
	Float64 f = ux * d + sx.f;

	if (!unsafe) {
		return f;
	} else {
		auto scale = Detail::Math::Bind64(1.0F);
		scale.exponent += i - (i >> unsafe);
		return f * scale.f;
	}
}

auto libbr_log_32(Float32 x) -> Float32 {
	return std::log(x);
}

auto libbr_log_64(Float64 x) -> Float64 {
	return std::log(x);
}

auto libbr_log2_32(Float32 x) -> Float32 {
	return std::log2(x);
}

auto libbr_log2_64(Float64 x) -> Float64 {
	return std::log2(x);
}

auto libbr_log10_32(Float32 x) -> Float32 {
	return std::log10(x);
}

auto libbr_log10_64(Float64 x) -> Float64 {
	return std::log10(x);
}

auto libbr_scale_d(DFloat x, SInt n) -> DFloat {
	return std::scalbln(x, n);
}

static constexpr auto _exponent32(UInt32 raw) -> SInt32 {
	return SInt32((raw >> 23) & 0xFFU) - 0x7F;
}

static constexpr auto _exponent64(UInt32 high) -> SInt32 {
	return SInt32((high >> 20) & 0x7FFU) - 0x3FF;
}

auto libbr_ceil_32(Float32 f) -> Float32 {
	auto bind = Detail::Math::Bind32(f);
	auto const exp = _exponent32(bind.r);
	if (exp < 0) { // |f| < 1
		if (bind.r > 0x7FFFFFFFU) { // f < 0
			// f = -0.0
			bind.r = 0x80000000U;
		} else if (bind.r != 0) { // f != +0.0
			// f = +1.0s
			bind.r = 0x3F800000U;
		}
	} else if (exp < 23) {
		UInt32 const mask = 0x007FFFFFU >> exp;
		if ((bind.r & mask) == 0) { // f is integral
			return f;
		}
		if (bind.r < 0x80000000U) { // f > 0
			bind.r += 0x00800000U >> exp;
		}
		bind.r &= ~mask;
	} else if (exp < 0x80) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return bind.f;
}

auto libbr_ceil_64(Float64 f) -> Float64 {
	auto bind = Detail::Math::Bind64(f);
	auto const exp = _exponent64(bind.h);
	if (exp < 0) { // |f| < 1
		if (bind.h > 0x7FFFFFFFU) { // f < 0
			// f <- -0.0
			bind.h = 0x80000000U;
			bind.l = 0x00000000U;
		} else if ((bind.h | bind.l) != 0) { // f != +0.0
			// f <- +1.0
			bind.h = 0x3FF00000U;
			bind.l = 0x00000000U;
		}
	} else if (exp < 20) {
		auto const mask = 0x000FFFFFU >> exp;
		if (((bind.h & mask) | bind.l) == 0) { // f is integral
			return f;
		}
		if (bind.h < 0x80000000U) { // f > 0
			bind.h += 0x00100000U >> exp;
		}
		bind.h &= ~mask;
		bind.l = 0x00000000U;
	} else if (exp < 52) {
		auto const mask = 0xFFFFFFFFU >> (exp - 20);
		if ((bind.l & mask) == 0) { // f is integral
			return f;
		}
		if (bind.h < 0x80000000U) { // f > 0
			if (exp == 20) {
				++bind.h;
			} else {
				auto x = bind.l + (1 << (52 - exp));
				if (x < bind.l) {
					++bind.h;
				}
				bind.l = x;
			}
		}
		bind.l &= ~mask;
	} else if (exp < 0x400) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return bind.f;
}

auto libbr_floor_32(Float32 f) -> Float32 {
	auto bind = Detail::Math::Bind32(f);
	auto const exp = _exponent32(bind.r);
	if (exp < 0) { // |f| < 1
		if (bind.r < 0x80000000) { // f > 0
			// f <- +0.0
			bind.r = 0x00000000U;
		} else if ((bind.r & 0x7FFFFFFFU) != 0) { // f != -0.0
			// f <- -1.0
			bind.r = 0xBF800000U;
		}
	} else if (exp < 23) {
		auto const mask = 0x007FFFFFU >> exp;
		if ((bind.r & mask) == 0) { // f is integral
			return f;
		}
		if (bind.r > 0x7FFFFFFFU) { // f < 0
			bind.r += 0x00800000U >> exp;
		}
		bind.r &= ~mask;
	} else if (exp < 0x80) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return bind.f;
}

auto libbr_floor_64(Float64 f) -> Float64 {
	auto bind = Detail::Math::Bind64(f);
	auto const exp = _exponent64(bind.h);
	if (exp < 0) {
		if (bind.h < 0x80000000U) { // f > 0
			// f <- +0.0
			bind.h = 0x00000000U;
			bind.l = 0x00000000U;
		} else if (((bind.h & 0x7FFFFFFFU) | bind.l) != 0) {
			// f <- -1.0
			bind.h = 0xBFF00000U;
			bind.l = 0x00000000U;
		}
	} else if (exp < 20) {
		auto const mask = 0x000FFFFFU >> exp;
		if (((bind.h & mask) | bind.l) == 0) { // f is integral
			return f;
		}
		if (bind.h > 0x7FFFFFFFU) { // f < 0
			bind.h += 0x00100000U >> exp;
		}
		bind.h &= ~mask;
		bind.l = 0U;
	} else if (exp < 52) {
		auto const mask = 0xFFFFFFFFU >> (exp - 20);
		if ((bind.l & mask) == 0) { // f is integral
			return f;
		}
		if (bind.h > 0x7FFFFFFFU) { // f < 0
			if (exp == 20) {
				++bind.h;
			} else {
				auto x = bind.l + (1 << (52 - exp));
				if (x < bind.l) {
					++bind.h;
				}
				bind.l = x;
			}
		}
		bind.l &= ~mask;
	} else if (exp < 0x400) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return bind.f;
}

auto libbr_truncate_32(Float32 f) -> Float32 {
	auto bind = Detail::Math::Bind32(f);
	auto const exp = _exponent32(bind.r);
	if (exp < 0) { // |f| < 1
		bind.r &= 0x80000000U;
	} else if (exp < 23) {
		bind.r = (bind.r & 0x80000000U) | (bind.r & ~(0x007FFFFFU >> exp));
	} else if (exp < 0x80) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return bind.f;
}

auto libbr_truncate_64(Float64 f) -> Float64 {
	auto bind = Detail::Math::Bind64(f);
	auto const exp = _exponent64(bind.h);
	if (exp < 0) { // |f| < 1
		bind.h &= 0x80000000U;
		bind.l = 0x00000000U;
	} else if (exp < 20) {
		bind.h = (bind.h & 0x80000000U) | (bind.h & ~(0x000FFFFFU >> exp));
		bind.l = 0x00000000U;
	} else if (exp < 52) {
		bind.l &= ~(0xFFFFFFFFU >> (exp - 20));
	} else if (exp < 0x400) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return bind.f;
}

auto libbr_round_32(Float32 f) -> Float32 {
	auto bind = Detail::Math::Bind32(f);
	auto const exp = _exponent32(bind.r);
	if (exp < 0) { // |f| < 1
		bind.r &= 0x80000000U;
		if (exp == -1) {
			bind.r |= 0x3F800000U;
		}
	} else if (exp < 23) {
		auto const mask = 0x007FFFFFU >> exp;
		if ((bind.r & mask) == 0) { // f is integral
			return f;
		}
		bind.r += 0x00400000U >> exp;
		bind.r &= ~mask;
	} else if (exp < 0x80) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return bind.f;
}

auto libbr_round_64(Float64 f) -> Float64 {
	auto bind = Detail::Math::Bind64(f);
	auto const exp = _exponent64(bind.h);
	if (exp < 0) { // |f| < 1
		bind.h &= 0x80000000U;
		if (exp == -1) {
			bind.h |= 0x3FF00000U;
		}
		bind.l = 0x00000000U;
	} else if (exp < 20) {
		auto const mask = 0x000FFFFFU >> exp;
		if (((bind.h & mask) | bind.l) == 0) { // f is integral
			return f;
		}
		bind.h += 0x00080000U >> exp;
		bind.h &= ~mask;
		bind.l = 0x00000000U;
	} else if (exp < 52) {
		auto const mask = 0xFFFFFFFFU >> (exp - 20);
		if ((bind.l & mask) == 0) { // f is integral
			return f;
		}
		auto x = bind.l + (1 << (51 - exp));
		if (x < bind.l) {
			++bind.h;
		}
		bind.l = x;
		bind.l &= ~mask;
	} else if (exp < 0x400) { // f is integral
		return f;
	} else { // f is inf or NaN
		return f + f;
	}
	return bind.f;
}

namespace BR {

template auto Complex<SFloat>::operator*(Complex const & y) const -> Complex;
template auto Complex<SFloat>::operator/(Complex const & y) const -> Complex;
template auto Complex<DFloat>::operator*(Complex const & y) const -> Complex;
template auto Complex<DFloat>::operator/(Complex const & y) const -> Complex;

} // namespace BR

