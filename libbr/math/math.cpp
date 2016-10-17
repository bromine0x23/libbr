#include <libbr/math/detail/float.hpp>
#include <libbr/math/exp2.hpp>
#include <libbr/math/ceil.hpp>
#include <libbr/math/floor.hpp>
#include <libbr/math/truncate.hpp>
#include <libbr/math/round.hpp>
#include <libbr/math/log.hpp>
#include <libbr/math/log2.hpp>
#include <libbr/math/log10.hpp>
#include <libbr/math/scale.hpp>
#include <libbr/math/complex.hpp>
#include <cmath>
#include <cfloat>

using namespace BR;

#if !defined(BR_GCC)
auto libbr_exp2_s(SFloat x) -> SFloat {
	return std::exp2(x);
}

auto libbr_log_s(SFloat x) -> SFloat {
	return std::log(x);
}

auto libbr_log2_s(SFloat x) -> SFloat {
	return std::log2(x);
}

auto libbr_log10_s(SFloat x) -> SFloat {
	return std::log10(x);
}

auto libbr_scale_s(SFloat x, SInt n) -> SFloat {
	return std::scalbln(x, n);
}
#endif

auto libbr_exp2_d(DFloat x) -> DFloat {
	return std::exp2(x);
}

auto libbr_log_d(DFloat x) -> DFloat {
	return std::log(x);
}

auto libbr_log2_d(DFloat x) -> DFloat {
	return std::log2(x);
}

auto libbr_log10_d(DFloat x) -> DFloat {
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


#if !defined(BR_GCC)
auto libbr_ceil_32(Float32 f) -> Float32 {
	auto bind = Detail::Float::Bind32{f};
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

auto libbr_floor_32(Float32 f) -> Float32 {
	auto bind = Detail::Float::Bind32{f};
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

auto libbr_truncate_32(Float32 f) -> Float32 {
	auto bind = Detail::Float::Bind32{f};
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

auto libbr_round_32(Float32 f) -> Float32 {
	auto bind = Detail::Float::Bind32{f};
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
#endif

auto libbr_ceil_64(Float64 f) -> Float64 {
	auto bind = Detail::Float::Bind64{f};
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

auto libbr_floor_64(Float64 f) -> Float64 {
	auto bind = Detail::Float::Bind64{f};
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

auto libbr_truncate_64(Float64 f) -> Float64 {
	auto bind = Detail::Float::Bind64{f};
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

auto libbr_round_64(Float64 f) -> Float64 {
	auto bind = Detail::Float::Bind64{f};
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

