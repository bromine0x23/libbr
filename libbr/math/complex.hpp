#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/copy_sign.hpp>
#include <libbr/math/make_infinity.hpp>
#include <libbr/math/function/is_finite.hpp>
#include <libbr/math/function/is_infinite.hpp>
#include <libbr/math/function/is_nan.hpp>
#include <libbr/math/function/abs.hpp>
#include <libbr/math/function/log2.hpp>
#include <libbr/math/function/max.hpp>
#include <libbr/math/scale.hpp>

namespace BR {

template< typename TValue >
class Complex;

template< typename TValue >
class Complex {

public:
	using Value = TValue;

	constexpr Complex(Value const & r = Value(), Value const & i = Value()) : m_r(r), m_i(i) {
	};

	constexpr Complex(Complex const & c) : m_r(c.m_r), m_i(c.m_i) {
	};

	template< typename TOtherValue >
	constexpr Complex(Complex<TOtherValue> const & c) : m_r(c.real()), m_i(c.imag()) {
	};

	auto operator=(Value const & y) -> Complex & {
		m_r = y;
		m_i = Value();
		return *this;
	}

	auto operator=(Complex const & c) -> Complex & {
		m_r = c.real();
		m_i = c.imag();
		return *this;
	}

	template< typename TOtherValue >
	auto operator=(Complex<TOtherValue> const & c) -> Complex & {
		m_r = c.real();
		m_i = c.imag();
		return *this;
	}

	constexpr auto real() const -> Value {
		return m_r;
	}

	constexpr auto imag() const -> Value {
		return m_i;
	}

	auto real(Value r) -> Complex & {
		m_r = r;
		return *this;
	}

	auto imag(Value i) -> Complex & {
		m_i = i;
		return *this;
	}

	constexpr auto operator==(Complex const & y) const -> bool {
		return real() == y.real() && imag() == y.imag();
	}

	constexpr auto operator==(Value const & y) const -> bool {
		return real() == y && imag() == 0;
	}

	constexpr auto operator!=(Complex const & y) const -> bool {
		return !(*this == y);
	}

	constexpr auto operator!=(Value const & y) const -> bool {
		return !(*this == y);
	}

	auto operator+=(Value const & y) -> Complex & {
		m_r += y;
		return *this;
	}

	auto operator-=(Value const & r) -> Complex & {
		m_r -= r;
		return *this;
	}

	auto operator*=(Value const & r) -> Complex & {
		m_r *= r;
		m_i *= r;
		return *this;
	}

	auto operator/=(Value const & r) -> Complex & {
		m_r /= r;
		m_i /= r;
		return *this;
	}

	template< typename TOtherValue >
	auto operator+=(Complex<TOtherValue> const & c) -> Complex & {
		m_r += c.real();
		m_i += c.imag();
		return *this;
	}

	template< typename TOtherValue >
	auto operator-=(Complex<TOtherValue> const & c) -> Complex & {
		m_r -= c.real();
		m_i -= c.imag();
		return *this;
	}

	template< typename TOtherValue >
	auto operator*=(Complex<TOtherValue> const & c) -> Complex & {
		*this = *this * Complex(c.real(), c.imag());
		return *this;
	}

	template< typename TOtherValue >
	auto operator/=(Complex<TOtherValue> const & c) -> Complex & {
		*this = *this / Complex(c.real(), c.imag());
		return *this;
	}

	auto operator+() const -> Complex {
		return *this;
	}

	auto operator-() const -> Complex {
		return Complex(-real(), -imag());
	}

	auto operator+(Value const & y) const -> Complex {
		auto z = *this;
		z += y;
		return z;
	}

	auto operator-(Value const & y) const -> Complex {
		auto z = *this;
		z -= y;
		return z;
	}

	auto operator*(Value const & y) const -> Complex {
		auto z = *this;
		z *= y;
		return z;
	}

	auto operator/(Value const & y) const -> Complex {
		auto z = *this;
		z /= y;
		return z;
	}

	auto operator+(Complex const & y) const -> Complex {
		auto z = *this;
		z += y;
		return z;
	}

	auto operator-(Complex const & y) const -> Complex {
		auto z = *this;
		z -= y;
		return z;
	}

	auto operator*(Complex const & y) const -> Complex;

	auto operator/(Complex const & y) const -> Complex;

private:
	Value m_r;
	Value m_i;

}; // class Complex<TValue>

template< typename TValue >
auto Complex<TValue>::operator*(Complex const & y) const -> Complex {
	auto xr = real();
	auto xi = imag();
	auto yr = y.real();
	auto yi = y.imag();
	auto xr_yr = xr * yr;
	auto xr_yi = xr * yi;
	auto xi_yr = xi * yr;
	auto xi_yi = xi * yi;
	auto zr = xr_yr - xi_yi;
	auto zi = xr_yi + xi_yr;
	if (is_nan(zr) && is_nan(zi)) {
		bool recalculate = false;
		if (is_infinite(xr) || is_infinite(xi)) {
			xr = copy_sign(is_infinite(xr) ? Value(1) : Value(0), xr);
			xi = copy_sign(is_infinite(xi) ? Value(1) : Value(0), xi);
			if (is_nan(yr)) {
				yr = copy_sign(Value(0), yr);
			}
			if (is_nan(yi)) {
				yi = copy_sign(Value(0), yi);
			}
			recalculate = true;
		}
		if (is_infinite(yr) || is_infinite(yi)) {
			yr = copy_sign(is_infinite(yr) ? Value(1) : Value(0), yr);
			yi = copy_sign(is_infinite(yi) ? Value(1) : Value(0), yi);
			if (is_nan(xr)) {
				xr = copy_sign(Value(0), xr);
			}
			if (is_nan(xi)) {
				xi = copy_sign(Value(0), xi);
			}
			recalculate = true;
		}
		if (!recalculate && (is_infinite(xr_yr) || is_infinite(xr_yi) || is_infinite(xi_yr) || is_infinite(xi_yi))) {
			if (is_nan(xr)) {
				xr = copy_sign(Value(0), xr);
			}
			if (is_nan(xi)) {
				xi = copy_sign(Value(0), xi);
			}
			if (is_nan(yr)) {
				yr = copy_sign(Value(0), yr);
			}
			if (is_nan(yi)) {
				yi = copy_sign(Value(0), yi);
			}
			recalculate = true;
		}
		if (recalculate) {
			zr = Value(make_infinity<Value>()) * (xr * yr - xi * yi);
			zi = Value(make_infinity<Value>()) * (xr * yi + xi * yr);
		}
	}
	return Complex(zr, zi);
}

template< typename TValue >
auto Complex<TValue>::operator/(Complex const & y) const -> Complex {
	auto xr = real();
	auto xi = imag();
	auto yr = y.real();
	auto yi = y.imag();
	auto log2_y = log2(max(abs(yr), abs(yi)));
	SInt i_log2_y = 0;
	if (is_finite(log2_y)) {
		i_log2_y = static_cast<SInt>(log2_y);
		yr = scale(yr, -i_log2_y);
		yi = scale(yi, -i_log2_y);
	}
	auto norm_y = yr * yr + yi * yi;
	auto zr = scale((xr * yr + xi * yi) / norm_y, -i_log2_y);
	auto zi = scale((xi * yr - xr * yi) / norm_y, -i_log2_y);
	if (is_nan(zr) && is_nan(zi)) {
		if ((norm_y == Value(0)) && (!is_nan(xr) || !is_nan(xi))) {
			zr = copy_sign(Value(make_infinity<Value>()), yr) * xr;
			zi = copy_sign(Value(make_infinity<Value>()), yr) * xi;
		} else if ((is_infinite(xr) || is_infinite(xi)) && is_finite(yr) && is_finite(yi)) {
			xr = copy_sign(is_infinite(xr) ? Value(1) : Value(0), xr);
			xi = copy_sign(is_infinite(xi) ? Value(1) : Value(0), xi);
			zr = Value(make_infinity<Value>()) * (xr * yr + xi * yi);
			zi = Value(make_infinity<Value>()) * (xi * yr - xr * yi);
		} else if (is_infinite(log2_y) && log2_y > Value(0) && is_finite(xr) && is_finite(xi)) {
			yr = copy_sign(is_infinite(yr) ? Value(1) : Value(0), yr);
			yi = copy_sign(is_infinite(yi) ? Value(1) : Value(0), yi);
			zr = Value(0) * (xr * yr + xi * yi);
			zi = Value(0) * (xi * yr - xr * yi);
		}
	}
	return Complex(zr, zi);
}

extern template auto Complex<SFloat>::operator*(Complex const & y) const -> Complex;
extern template auto Complex<SFloat>::operator/(Complex const & y) const -> Complex;
extern template auto Complex<DFloat>::operator*(Complex const & y) const -> Complex;
extern template auto Complex<DFloat>::operator/(Complex const & y) const -> Complex;

} // namespace BR