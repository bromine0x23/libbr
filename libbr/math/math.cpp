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

auto ceil(Float32 f) -> Float32 {
	UInt32 raw = Detail::Math::to_raw(f);
	SInt32 const exp = SInt32((raw >> 23) & 0xFFU) - 0x7F;
	if (exp < 23) {
		if (exp < 0) {
			if (raw < 0) {
				raw = 0x80000000U;
			} else if (raw != 0) {
				raw = 0x3F800000U;
			}
		} else {
			auto const mask = 0x007FFFFFU >> exp;
			if ((raw & mask) == 0) {
				return f;
			}
			if (raw > 0) {
				raw += UInt32(0x00800000U) >> exp;
			}
			raw &= ~mask;
		}
	} else if (exp == 0x80) {
		return f + f;
	} else {
		return f;
	}
	return Detail::Math::to_float32(raw);
}

auto ceil(Float64 f) -> Float64 {
	UInt32 high = Detail::Math::get_high_part(f);
	UInt32 low = Detail::Math::get_low_part(f);
	SInt32 const exp = SInt32((high >> 20) & 0x7FFU) - 0x3FF;
	if (exp < 20) {
		if (exp < 0) {
			if (high < 0) {
				high = 0x80000000U;
				low = 0x00000000U;
			} else if ((high | low) != 0) {
				high = 0x3FF00000U;
				low = 0x00000000U;
			}
		} else {
			auto const mask = 0x000FFFFFU >> exp;
			if (((high & mask) | low) == 0) {
				return f;
			}
			if (high > 0) {
				high += 0x00100000U >> exp;
			}
			high &= ~mask;
			low = 0;
		}
	} else if (exp > 51) {
		if (exp == 0x400) {
			return f + f;
		} else {
			return f;
		}
	} else {
		auto const mask = 0xFFFFFFFFU >> (exp - 20);
		if ((low & mask) == 0) {
			return f;
		}
		if (high > 0) {
			if (exp == 20) {
				high += 1;
			} else {
				UInt32 q = low + (1 << (52 - exp));
				if (q < low) {
					high += 1;
				}
				low = q;
			}
		}
		low &= ~mask;
	}
	return Detail::Math::to_float64(high, low);
}

auto floor(Float32 f) -> Float32 {
	UInt32 raw = Detail::Math::to_raw(f);
	SInt32 const exp = SInt32((raw >> 23) & 0xFFU) - 0x7F;
	if (exp < 23) {
		if (exp < 0) {
			if (raw >= 0) {
				raw = 0;
			} else if ((raw & 0x7FFFFFFFU) != 0) {
				raw = 0xbf800000;
			}
		} else {
			auto const mask = 0x007FFFFFU >> exp;
			if ((raw & mask) == 0) {
				return f;
			}
			if (raw < 0) {
				raw += UInt32(0x00800000U) >> exp;
			}
			raw &= ~mask;
		}
	} else if (exp == 0x80) {
		return f + f;
	} else {
		return f;
	}
	return Detail::Math::to_float32(raw);
}

auto floor(Float64 f) -> Float64 {
	UInt32 high = Detail::Math::get_high_part(f);
	UInt32 low = Detail::Math::get_low_part(f);
	SInt32 const exp = SInt32((high >> 20) & 0x7FFU) - 0x3FF;
	if (exp < 20) {
		if (exp < 0) {
			if (high >= 0) {
				high = 0;
				low = 0;
			} else if (((high & 0x7FFFFFFF) | low) != 0) {
				high = 0xBFF00000;
				low = 0;
			}
		} else {
			auto const mask = 0x000FFFFFU >> exp;
			if (((high & mask) | low) == 0) {
				return f;
			}
			if (high < 0) {
				high += 0x00100000U >> exp;
			}
			high &= ~mask;
			low = 0;
		}
	} else if (exp > 51) {
		if (exp == 0x400) {
			return f + f;
		} else {
			return f;
		}
	} else {
		auto const mask = 0xFFFFFFFFU >> (exp - 20);
		if ((low & mask) == 0) {
			return f;
		}
		if (high < 0) {
			if (exp == 20) {
				high += 1;
			} else {
				UInt32 x = low + (1 << (52 - exp));
				if (x < low) {
					high += 1;
				}
				low = x;
			}
		}
		low &= ~mask;
	}
	return Detail::Math::to_float64(high, low);
}

auto truncate(Float32 f) -> Float32 {
	UInt32 raw = Detail::Math::to_raw(f);
	SInt32 const exp = SInt32((raw >> 23) & 0xFFU) - 0x7F;
	if (exp < 23) {
		UInt32 s = raw & 0x80000000U;
		if (exp < 0) {
			return Detail::Math::to_float32(s);
		} else {
			return Detail::Math::to_float32(s | (raw & ~(UInt32(0x007FFFFFU) >> exp)));
		}
	} else {
		if (exp == 0x80) {
			return f + f;
		}
	};
	return f;
}

} // namespace BR

