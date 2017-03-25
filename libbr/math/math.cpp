#include <libbr/math/detail/bind.hpp>
#include <libbr/math/complex.hpp>
#include <libbr/math/float.hpp>
#include <cmath>
#include <cfloat>
#include <cfenv>

using namespace BR;
using Detail::Math::Bind32;
using Detail::Math::Bind64;

namespace _32 {

constexpr static Float32 _1  = 1.0; // 1

constexpr static Float32 tiny  = 1E-30; // 1E-30

static Float32 const _2_POW_P127  = Bind32(0x7F000000U).f; // 2 ^ +127

static Float32 const _2_POW_M100  = Bind32(0x0D800000U).f; // 2 ^ -100

static Float32 const _3_MUL_2_POW_P14 = Bind32(0x47400000U).f; // 3 * 2^+14

static Float32 const _3_MUL_2_POW_P22 = Bind32(0x4b400000U).f; // 3 * 2^+22

static Float32 const _3_MUL_2_POW_P42 = Bind32(0x42A80000U).f; // 3 * 2^+42

static Float32 const _1_DIV_LN2 = Bind32(0x3FB8AA3BU).f; // 1 / ln(2)

static Float32 const _LN2 = Bind32(0x3F317218U).f; // ln(2)

} // inline namespace _32

namespace _64 {

static Float64 const _2_POW_P1023 = Bind64(0x7FE00000U, 0U).f; // 2 ^ +1023

static Float64 const _2_POW_M1000  = Bind64(0x01700000U, 0U).f; // 2 ^ -1000

static Float64 const _3_MUL_2_POW_P42 = Bind64(0x42A80000U, 0U).f; // 3 * 2^+42

} // inline namespace _64

auto libbr_sqrt_32(Float32 x) -> Float32 {
	using namespace _32;

	Bind32 b(x);
	SInt32 m = b.exponent;
	switch (classify(x)) {
		case FloatCategory::NaN:
			BR_FALLTHROUGH;
		case FloatCategory::Infinite:
			return x * x + x;
		case FloatCategory::Zero:
			return x;
		case FloatCategory::Normal:
			if (x < 0) {
				return (x - x) / (x - x);
			}
			break;
		case FloatCategory::SubNormal:
			{
				SInt i = 0;
				for (i = 0; (b.r & 0x00800000U) == 0; ++i) {
					b.r <<= 1;
				}
				m -= i - 1;
			}
			break;
	}

	m -= 127;
	b.r = (b.r & 0x007FFFFFU) | 0x00800000U;
	if ((m & 1) != 0) {
		b.r += b.r;
	}
	m >>= 1;

	b.r += b.r;

	UInt32 q = 0;

	for (UInt32  s = 0, r = 0x01000000U; r != 0; r >>= 1) {
		UInt32 t = s + r;
		if (t <= b.r) {
			s    = t + r;
			b.r -= t;
			q   += r;
		}
		b.r += b.r;
	}

	if (b.r != 0) {
		Float32 z = _1 - tiny;
		if (z >= _1) {
			z = _1 + tiny;
			if (z > _1) {
				q += 2;
			} else {
				q += (q & 1);
			}
		}
	}

	b.r = (q >> 1) + 0x3F000000U;
	b.r += m << 23;
	return b.f;
}

auto libbr_sqrt_64(Float64 x) -> Float64 {
	using namespace _64;

	Bind64 b(x);
	SInt32 m = b.exponent;

	switch (classify(x)) {
		case FloatCategory::NaN:
			BR_FALLTHROUGH;
		case FloatCategory::Infinite:
			return x * x + x;
		case FloatCategory::Zero:
			return x;
		case FloatCategory::Normal:
			if (x < 0) {
				return (x - x) / (x - x);
			}
			break;
		case FloatCategory::SubNormal: {
			SInt i = 0;
			for (i = 0; (b.r & 0x00800000U) == 0; ++i) {
				b.r <<= 1;
			}
			m -= i - 1;
		}
			break;
	}

	return b.f;
}

auto libbr_cbrt_32(Float32 x) -> Float32 {
	return std::cbrt(x); // TODO
}

auto libbr_cbrt_64(Float64 x) -> Float64 {
	return std::cbrt(x); // TODO
}

auto libbr_pow_32(Float32 base, Float32 exponent) -> Float32 {
	return std::pow(base, exponent); // TODO
}

auto libbr_pow_64(Float64 base, Float64 exponent) -> Float64 {
	return std::pow(base, exponent); // TODO
}

auto libbr_hypot_32(Float32 x, Float32 y) -> Float32 {
	return std::hypot(x, y); // TODO
}

auto libbr_hypot_64(Float64 x, Float64 y) -> Float64 {
	return std::hypot(x, y); // TODO
}

#include <libbr/math/function/detail/exp.inl>

auto libbr_exp_32(Float32 x) -> Float32 {
	using namespace _32;

	static const Float32 HMARK = Bind32(0x42B17218U).f;
	static const Float32 LMARK = Bind32(0xC2CFF1B5U).f;

	if (is_less(x, HMARK)) {
		if (!is_greater(x, LMARK)) {
			if (is_infinite(x)) {
				return 0; // x == -inf, e^-inf == 0
			} else {
				return _2_POW_M100 * _2_POW_M100; // underflow
			}
		}
	} else {
		return _2_POW_P127 * x; // Return x, if x is a NaN or Inf; or overflow, otherwise.
	}

	// x = n * ln(2) + t / 512 + delta[t] + x;

	Float32 n = x * _1_DIV_LN2 + _3_MUL_2_POW_P22; n -= _3_MUL_2_POW_P22;

	Float32 dx = x - n * _LN2;

	Float32 t = dx + _3_MUL_2_POW_P42; t -= _3_MUL_2_POW_P42;

	dx -= t;

	auto i = SInt(t * 512.0F);

	Float32 d;
	if (t >= 0)
		d = - EXP_32_DELTA[i];
	else
		d = EXP_32_DELTA[-i];

	auto sx = Bind32(EXP_32_ACCURATE[i + 177]);
	sx.exponent += SInt(n);

	Float32 ux = (0.5000000496709180453F * dx + 1.0000001192102037084F) * dx + d;

	Float32 result = ux * sx.f + sx.f;

	return result;
}

auto libbr_exp_64(Float64 x) -> Float64 {
	return std::exp(x); // TODO
}

#include <libbr/math/function/detail/exp2.inl>

auto libbr_exp2_32(Float32 x) -> Float32 {
	using namespace _32;

	static constexpr Float32 HMARK = FLT_MAX_EXP;
	static constexpr Float32 LMARK = FLT_MIN_EXP - FLT_MANT_DIG - 1;

	if (is_less(x, HMARK)) {
		if (!is_greater(x, LMARK)) {
			if (is_infinite(x)) {
				return 0; // x == -inf, e^-inf == 0
			} else {
				return _2_POW_M100 * _2_POW_M100; // underflow
			}
		}
	} else {
		return _2_POW_P127 * x; // Return x, if x is a NaN or Inf; or overflow, otherwise.
	}

	// x = ex + t / 512 + r, -128 <= t < 128, -1/512 <= r <= 1/512

	// mx = ex + t / 256
	Float32 mx = x + _3_MUL_2_POW_P14; mx -= _3_MUL_2_POW_P14;

	// r
	Float32 r = x - mx;

	// i = (ex * 256 + t) + 128 = mx * 256 + 128
	auto i = SInt(mx * 256.0F + 128.0F);

	// x = ex + t / 256 + e + d, -7E-4 < e < 7E-4, 2^(t / 256 + e) === 2^-64

	Float32 d = r - Bind32(EXP2_32_DELTA[i & 0xFF]).f;

	// sx = 2^(t/255 + e + ex)
	auto sx = Bind32(EXP2_32_ACCURATE[i & 0xFF]);

	i >>= 8;

	bool unsafe = abs(i) >= 124;
	sx.exponent += i >> unsafe;

	Float32 ux = (.24022656679F * d + .69314736128F) * sx.f;

	Float32 result = ux * d + sx.f;
	if (!unsafe) {
		return result;
	} else {
		auto scale = Bind32(1.0F);
		scale.exponent += i - (i >> unsafe);
		return result * scale.f;
	}
}

auto libbr_exp2_64(Float64 x) -> Float64 {
	using namespace _64;

	static constexpr Float64 HMARK = DBL_MAX_EXP;
	static constexpr Float64 LMARK = DBL_MIN_EXP - DBL_MANT_DIG - 1;

	if (is_less(x, HMARK)) {
		if (!is_greater(x, LMARK)) {
			if (is_infinite(x)) {
				return 0; // x == -inf, e^-inf == 0
			} else {
				return _2_POW_M1000 * _2_POW_M1000; // underflow
			}
		}
	} else {
		return _2_POW_P1023 * x; // Return x, if x is a NaN or Inf; or overflow, otherwise.
	}

	// x = ex + t / 512 + r, -256 <= t < 256, -1/1024 <= r <= 1/1024

	// mx = ex + t / 256
	Float64 mx = x + _3_MUL_2_POW_P42; mx -= _3_MUL_2_POW_P42;

	// r
	Float64 r = x - mx;

	// i = (ex * 512 + t) + 256 = mx * 512 + 256
	auto i = SInt(mx * 512.0 + 256.0);

	// x = ex + t / 256 + e + d, -7E-4 < e < 7E-4, 2^(t / 256 + e) === 2^-64
	Float64 d = r - Bind64(EXP2_64_DELTA[i & 0x1FF], 0U).f;

	// sx = 2^(t/512 + e + ex)
	auto sx = Bind64(EXP2_64_ACCURATE[i & 0x1FF]);

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
		auto scale = Bind64(1.0F);
		scale.exponent += i - (i >> unsafe);
		return f * scale.f;
	}
}

auto libbr_log_32(Float32 x) -> Float32 {
	return std::log(x); // TODO
}

auto libbr_log_64(Float64 x) -> Float64 {
	return std::log(x); // TODO
}

auto libbr_log2_32(Float32 x) -> Float32 {
	return std::log2(x); // TODO
}

auto libbr_log2_64(Float64 x) -> Float64 {
	return std::log2(x); // TODO
}

auto libbr_log10_32(Float32 x) -> Float32 {
	return std::log10(x); // TODO
}

auto libbr_log10_64(Float64 x) -> Float64 {
	return std::log10(x); // TODO
}

#if !defined(BR_GCC)
auto libbr_scale_s(SFloat x, SInt n) -> SFloat {
	return std::scalblnf(x, n);
}
#endif

auto libbr_scale_d(DFloat x, SInt n) -> DFloat {
	return std::scalbln(x, n);
}

auto libbr_sin_32(Float32 x) -> Float32 {
	return std::sin(x); // TODO
}

auto libbr_sin_64(Float64 x) -> Float64 {
	return std::sin(x); // TODO
}

auto libbr_cos_32(Float32 x) -> Float32 {
	return std::cos(x); // TODO
}

auto libbr_cos_64(Float64 x) -> Float64 {
	return std::cos(x); // TODO
}

auto libbr_tan_32(Float32 x) -> Float32 {
	return std::tan(x); // TODO
}

auto libbr_tan_64(Float64 x) -> Float64 {
	return std::tan(x); // TODO
}

auto libbr_arcsin_32(Float32 x) -> Float32 {
	return std::asin(x); // TODO
}

auto libbr_arcsin_64(Float64 x) -> Float64 {
	return std::asin(x); // TODO
}

auto libbr_arccos_32(Float32 x) -> Float32 {
	return std::acos(x); // TODO
}

auto libbr_arccos_64(Float64 x) -> Float64 {
	return std::acos(x); // TODO
}

auto libbr_arctan_32(Float32 x) -> Float32 {
	return std::atan(x); // TODO
}

auto libbr_arctan_64(Float64 x) -> Float64 {
	return std::atan(x); // TODO
}


auto libbr_sinh_32(Float32 x) -> Float32 {
	return std::sinh(x); // TODO
}

auto libbr_sinh_64(Float64 x) -> Float64 {
	return std::sinh(x); // TODO
}

auto libbr_cosh_32(Float32 x) -> Float32 {
	return std::cosh(x); // TODO
}

auto libbr_cosh_64(Float64 x) -> Float64 {
	return std::cosh(x); // TODO
}

auto libbr_tanh_32(Float32 x) -> Float32 {
	return std::tanh(x); // TODO
}

auto libbr_tanh_64(Float64 x) -> Float64 {
	return std::tanh(x); // TODO
}

auto libbr_arcsinh_32(Float32 x) -> Float32 {
	return std::asinh(x); // TODO
}

auto libbr_arcsinh_64(Float64 x) -> Float64 {
	return std::asinh(x); // TODO
}

auto libbr_arccosh_32(Float32 x) -> Float32 {
	return std::acosh(x); // TODO
}

auto libbr_arccosh_64(Float64 x) -> Float64 {
	return std::acosh(x); // TODO
}

auto libbr_arctanh_32(Float32 x) -> Float32 {
	return std::atanh(x); // TODO
}

auto libbr_arctanh_64(Float64 x) -> Float64 {
	return std::atanh(x); // TODO
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

