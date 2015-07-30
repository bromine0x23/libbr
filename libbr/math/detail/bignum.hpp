#pragma once

#include <libbr/config.hpp>
#include <libbr/math/detail/bignum_config.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/math/sign.hpp>
#include <libbr/utility/bit_math.hpp>
#include <libbr/utility/initializer_list.hpp>
#include <libbr/utility/integer_constant.hpp>
#include <libbr/utility/swap.hpp>

#include <string>

namespace BR {
namespace Detail {
namespace Bignum {

template< typename T >
constexpr T mul_radix(T x) { return x << BIT_PER_DIGIT; }

template< typename T >
constexpr T div_radix(T x) { return x >> BIT_PER_DIGIT; }

template< typename T >
constexpr Digit mod_radix(T x) { return Digit(x & Digit(-1)); }

template< typename TInt >
constexpr Sign separate_sign(TInt & v) noexcept {
	return (v < 0) ? (v = -v, Sign::NEG) : Sign::ZPOS;
}

constexpr Sign   sign(Imp const & X) noexcept { return X.sign; }
constexpr Sign & sign(Imp       & X) noexcept { return X.sign; }

constexpr Size   length(Imp const & X) noexcept { return X.length; }
constexpr Size & length(Imp       & X) noexcept { return X.length; }

constexpr Size   capacity(Imp const & X) noexcept { return X.capacity; }
constexpr Size & capacity(Imp       & X) noexcept { return X.capacity; }

constexpr Digit const *   digits(Imp const & X) noexcept { return X.digits; }
constexpr Digit       * & digits(Imp       & X) noexcept { return X.digits; }

constexpr Size bit_length(Imp const & X) noexcept {
	return length(X) * BIT_PER_DIGIT - count_leading_zeros(digits(X)[length(X) - 1]);
}

constexpr Digit bit(Imp const & X, Size index) noexcept {
	return (digits(X)[index / BIT_PER_DIGIT] >> (index & (BIT_PER_DIGIT - 1))) & 1;
}

inline void init(Imp & X) {
	sign(X) = Sign::ZPOS;
	length(X) = 0;
	capacity(X) = 0;
	digits(X) = nullptr;
}

inline void clear(Imp & X) noexcept {
	delete [] digits(X);
	length(X) = 0;
	capacity(X) = 0;
	digits(X) = nullptr;
}

void reserve(Imp & X, Size size);

inline void set0(Imp & X) {
	reserve(X, 1);
	sign(X) = Sign::ZPOS;
	digits(X)[0] = 0;
	length(X)  = 1;
}


inline void set_d(Imp & X, Digit d) {
	reserve(X, 1);
	sign(X) = Sign::ZPOS;
	digits(X)[0] = d;
	length(X)  = 1;
}

template< typename TInt >
inline void set_int(Imp & X, TInt v, IntegerConstant< Size, 1 >) {
	reserve(X, 1);
	digits(X)[0] = Digit(v);
	length(X) = 1;
}

template< typename TInt >
inline void set_int(Imp & X, TInt v, IntegerConstant< Size, 2 >) {
	reserve(X, 2);
	digits(X)[0] = mod_radix(v);
	if ((v = div_radix(v)) != 0) {
		digits(X)[1] = Digit(v);
		length(X) = 2;
	} else {
		length(X) = 1;
	}
}

template< typename TInt, Size size >
inline void set_int(Imp & X, TInt v, IntegerConstant< Size, size >) {
	reserve(X, size);
	for (Size i = 0; v != 0; ++i, v = div_radix(v)) {
		digits(X)[i] = mod_radix(v);
		length(X) = i;
	}
}

template< typename TUInt >
inline void set_uint(Imp & X, TUInt v) {
	sign(X) = Sign::ZPOS;
	set_int(X, v, IntegerConstant< Size, (sizeof(TUInt) + sizeof(Digit) - 1) / sizeof(Digit) >{});
}

template< typename TSInt >
inline void set_sint(Imp & X, TSInt v) {
	sign(X) = separate_sign(v);
	set_int(X, v, IntegerConstant< Size, (sizeof(TSInt) + sizeof(Digit) - 1) / sizeof(Digit) >{});
}

void set_power2(Imp & X, Size n);

void copy(Imp & X, Imp const & Y);

void copy_list(Imp & X, InitializerList<Digit> L);

inline void fake(Imp & X, Digit const * ds, Size size) noexcept {
	sign(X) = Sign::ZPOS;
	capacity(X) = length(X) = size;
	digits(X) = const_cast<Digit *>(ds);
}

inline void fake_ud(Imp & X, UDigit & d) noexcept {
	sign(X) = Sign::ZPOS;
	capacity(X) = length(X) = 1;
	digits(X) = reinterpret_cast<Digit *>(&d);
}

inline void fake_sd(Imp & X, SDigit & d) noexcept {
	sign(X) = separate_sign(d);
	capacity(X) = length(X) = 1;
	digits(X) = reinterpret_cast<Digit *>(&d);
}

inline void swap(Imp & X, Imp & Y) noexcept {
	BR::swap(X, Y);
}

constexpr bool is0(Imp const & X) {
	return length(X) == 1 && digits(X)[0] == 0;
}

Relation cmp_u(Imp const & X, Imp const & Y);

inline Relation cmp(Imp const & X, Imp const & Y) {
	if (sign(X) == sign(Y)) {
		if (sign(X) == Sign::ZPOS) {
			return cmp_u(X, Y);
		}
		else {
			return cmp_u(Y, X);
		}
	} else {
		if (sign(X) == Sign::ZPOS) {
			return Relation::GT;
		}
		else {
			return Relation::LT;
		}
	}
}

void conj(Imp & X);

void add_u(Imp const & X, Imp const & Y, Imp & Z);
void sub_u(Imp const & X, Imp const & Y, Imp & Z);

inline void add(Imp const & X, Imp const & Y, Imp & Z) {
	if (sign(X) == sign(Y)) {
		if (length(X) < length(Y)) {
			sign(Z) = sign(X);
			add_u(Y, X, Z);
		} else {
			sign(Z) = sign(X);
			add_u(X, Y, Z);
		}
	} else {
		if (cmp_u(X, Y) == Relation::LT) {
			sign(Z) = -sign(X);
			sub_u(Y, X, Z);
		} else {
			sign(Z) = +sign(X);
			sub_u(X, Y, Z);
		}
	}
}

inline void sub(Imp const & X, Imp const & Y, Imp & Z) {
	if (sign(X) != sign(Y)) {
		if (length(X) < length(Y)) {
			sign(Z) = sign(X);
			add_u(Y, X, Z);
		} else {
			sign(Z) = sign(X);
			add_u(X, Y, Z);
		}
	} else {
		if (cmp_u(X, Y) == Relation::LT) {
			sign(Z) = -sign(X);
			sub_u(Y, X, Z);
		} else {
			sign(Z) = +sign(X);
			sub_u(X, Y, Z);
		}
	}
}

inline void add_ud(Imp const & X, UDigit d, Imp & Z) {
	Imp Y;
	fake_ud(Y, d);
	add(X, Y, Z);
}

inline void add_sd(Imp const & X, SDigit d, Imp & Z) {
	Imp Y;
	fake_sd(Y, d);
	add(X, Y, Z);
}

inline void sub_ud(Imp const & X, UDigit d, Imp & Z) {
	Imp Y;
	fake_ud(Y, d);
	sub(X, Y, Z);
}

inline void sub_sd(Imp const & X, SDigit d, Imp & Z) {
	Imp Y;
	fake_sd(Y, d);
	sub(X, Y, Z);
}

void mul(Imp const & X, Imp const & Y, Imp & Z);

void mul_d(Imp const & X, Digit d, Imp & Z);

inline void mul_ud(Imp const & X, UDigit d, Imp & Z) {
	sign(Z) = sign(X);
	mul_d(X, static_cast<Digit>(d), Z);
}

inline void mul_sd(Imp const & X, SDigit d, Imp & Z) {
	sign(Z) = sign(X) * separate_sign(d);
	mul_d(X, static_cast<Digit>(d), Z);
}

void div_mod(Imp const & X, Imp const & Y, Imp * Q, Imp * R);

inline void div(Imp const & X, Imp const & Y, Imp & Z) {
	div_mod(X, Y, &Z, nullptr);
}

inline void mod(Imp const & X, Imp const & Y, Imp & Z) {
	div_mod(X, Y, nullptr, &Z);
}

Digit div_mod_d(Imp const & X, Digit d, Imp & Z);

inline Digit div_mod_ud(Imp const & X, UDigit d, Imp & Z) {
	sign(Z) = sign(X);
	return div_mod_d(X, static_cast<Digit>(d), Z);
}

inline Digit div_mod_sd(Imp const & X, SDigit d, Imp & Z) {
	sign(Z) = sign(X) / separate_sign(d);
	return div_mod_d(X, static_cast<Digit>(d), Z);
}

inline void div_d(Imp const & X, Digit d, Imp & Z) {
	div_mod_d(X, d, Z);
}

inline void div_ud(Imp const & X, UDigit d, Imp & Z) {
	sign(Z) = sign(X);
	div_d(X, static_cast<Digit>(d), Z);
}

inline void div_sd(Imp const & X, SDigit d, Imp & Z) {
	sign(Z) = sign(X) / separate_sign(d);
	div_d(X, static_cast<Digit>(d), Z);
}

Digit mod_d(Imp const & X, UDigit d);

void bor (Imp const & X, Imp const & Y, Imp & Z);

void band(Imp const & X, Imp const & Y, Imp & Z);

void bxor(Imp const & X, Imp const & Y, Imp & Z);

inline void bor_ud (Imp const & X, UDigit d, Imp & Z) {
	Imp Y;
	fake_ud(Y, d);
	bor(X, Y, Z);
}

inline void bor_sd (Imp const & X, SDigit d, Imp & Z) {
	Imp Y;
	fake_sd(Y, d);
	bor (X, Y, Z);
}

inline void band_ud(Imp const & X, UDigit d, Imp & Z) {
	Imp Y;
	fake_ud(Y, d);
	band(X, Y, Z);
}

inline void band_sd(Imp const & X, SDigit d, Imp & Z) {
	Imp Y;
	fake_sd(Y, d);
	band(X, Y, Z);
}

inline void bxor_ud(Imp const & X, UDigit d, Imp & Z) {
	Imp Y;
	fake_ud(Y, d);
	bxor(X, Y, Z);
}

inline void bxor_sd(Imp const & X, SDigit d, Imp & Z) {
	Imp Y;
	fake_sd(Y, d);
	bxor(X, Y, Z);
}

void sqr(Imp const & X, Imp & Z);

void power(Imp const & X, Digit n, Imp & Z);

void mul2(Imp const & X, Imp & Z);

void div2(Imp const & X, Imp & Z);

void lsh_b(Imp const & X, Digit bn, Imp & Z);

void rsh_b(Imp const & X, Digit bn, Imp & Z);

inline void lsh_b_ud(Imp const & X, UDigit bn, Imp & Z) {
	lsh_b(X, static_cast<Digit>(bn), Z);
}

inline void rsh_b_ud(Imp const & X, UDigit bn, Imp & Z) {
	rsh_b(X, static_cast<Digit>(bn), Z);
}

inline void lsh_b_sd(Imp const & X, SDigit bn, Imp & Z) {
	if (bn < 0) {
		rsh_b(X, static_cast<Digit>(-bn), Z);
	} else {
		lsh_b(X, static_cast<Digit>(bn), Z);
	}
}

inline void rsh_b_sd(Imp const & X, SDigit bn, Imp & Z) {
	if (bn < 0) {
		lsh_b(X, static_cast<Digit>(-bn), Z);
	} else {
		rsh_b(X, static_cast<Digit>(bn), Z);
	}
}

void lsh_d(Imp const & X, Digit dn, Imp & Z);

void rsh_d(Imp const & X, Digit dn, Imp & Z);

inline void lsh_d_ud(Imp const & X, UDigit dn, Imp & Z) {
	lsh_d(X, static_cast<Digit>(dn), Z);
}

inline void rsh_d_ud(Imp const & X, UDigit dn, Imp & Z) {
	rsh_d(X, static_cast<Digit>(dn), Z);
}

inline void lsh_d_sd(Imp const & X, SDigit dn, Imp & Z) {
	if (dn < 0) {
		rsh_d(X, static_cast<Digit>(-dn), Z);
	} else {
		lsh_d(X, static_cast<Digit>(dn), Z);
	}
}

inline void rsh_d_sd(Imp const & X, SDigit dn, Imp & Z) {
	if (dn < 0) {
		lsh_d(X, static_cast<Digit>(-dn), Z);
	} else {
		rsh_d(X, static_cast<Digit>(dn), Z);
	}
}

void lsh(Imp const & X, Digit n, Imp & Z);

void rsh(Imp const & X, Digit n, Imp & Z);

inline void lsh_ud(Imp const & X, UDigit n, Imp & Z) {
	lsh(X, static_cast<Digit>(n), Z);
}

inline void rsh_ud(Imp const & X, UDigit n, Imp & Z) {
	rsh(X, static_cast<Digit>(n), Z);
}

inline void lsh_sd(Imp const & X, SDigit n, Imp & Z) {
	if (n < 0) {
		rsh(X, static_cast<Digit>(-n), Z);
	} else {
		lsh(X, static_cast<Digit>(n), Z);
	}
}

inline void rsh_sd(Imp const & X, SDigit n, Imp & Z) {
	if (n < 0) {
		lsh(X, static_cast<Digit>(-n), Z);
	} else {
		rsh(X, static_cast<Digit>(n), Z);
	}
}

std::string inspect(Imp const & X);

std::string to_s(Imp const & X, Digit b, bool show_plus);

} // namespace Bignum
} // namespace Detail
} // namespace BR