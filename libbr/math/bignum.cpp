#include <libbr/math/bignum.hpp>

#include <libbr/utility/bit_math.hpp>
#include <libbr/utility/swap.hpp>

#include <stdexcept>

#include <sstream>
#include <iomanip>

#include <cstdio>
#include <iostream>

namespace BR {
namespace Math {

namespace {

using Sign     = Bignum::Sign;
// using Relation = Relation;
using Digit    = Bignum::Digit;
using UDigit   = Bignum::UDigit;
using SDigit   = Bignum::SDigit;
using DDigit   = Bignum::DDigit;
using UDDigit  = Bignum::UDDigit;
using SDDigit  = Bignum::SDDigit;

constexpr static auto BITS_PER_DIGIT = Bignum::BITS_PER_DIGIT;
constexpr static auto RADIX = Bignum::RADIX;

template< typename type >
static inline type mul_radix(type x) {
	return x << BITS_PER_DIGIT;
}

template< typename type >
static inline type div_radix(type x) {
	return x >> BITS_PER_DIGIT;
}

template< typename type >
static inline type mod_radix(type x) {
	return x & Digit(-1);
}

constexpr static auto DIGIT_PER_BLOCK = 8;

constexpr static inline Size align_mask() {
	return ~(DIGIT_PER_BLOCK - 1);
}

constexpr static inline Size align_size(Size size) {
	return (size + DIGIT_PER_BLOCK - 1) & align_mask();
}

constexpr static auto MUL_DOOR_KARATSUBA = 80;
constexpr static auto MUL_DOOR_TOOM      = 360;
constexpr static auto SQR_DOOR_KARATSUBA = 120;
constexpr static auto SQR_DOOR_TOOM      = 420;

template< typename TFunctor >
static inline void duff_device(Size size, TFunctor functor) {
	auto count = size >> 3;
	switch (size & 7) {
		default:
			BR_ASSERT(false);
		do {
			functor(); case 7:;
			functor(); case 6:;
			functor(); case 5:;
			functor(); case 4:;
			functor(); case 3:;
			functor(); case 2:;
			functor(); case 1:;
			functor(); case 0:;
		} while (count-- > 0);
	}
}

template< Size bits_per_digit >
struct BaseTraits {
	// chars_per_digit[base] = the largest power of base that fits a Digit
	constexpr static UInt8 chars_per_digit[] = {};

	// big_base[base] = base ** chars_per_digit[base]
	constexpr static UInt8 big_base[] = {};
};

template<>
struct BaseTraits< 8 > {
	constexpr static UInt8 chars_per_digit[] = {
		0, 0, 7, 5, 3, 3, 3, 2,
		2, 2, 2, 2, 2, 2, 2, 2,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
	};
	constexpr static UInt8 big_base[] = {
		   0,    0, 0x80, 0xf3, 0x40, 0x7d, 0xd8, 0x31,
		0x40, 0x51, 0x64, 0x79, 0x90, 0xa9, 0xc4, 0xe1,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
		0x20, 0x21, 0x22, 0x23, 0x24,
	};
};

template<>
struct BaseTraits< 16 > {
	constexpr static UInt8 chars_per_digit[] = {
		 0,  0, 15, 10,  7,  6,  6,  5,
		 5,  5,  4,  4,  4,  4,  4,  4,
		 3,  3,  3,  3,  3,  3,  3,  3,
		 3,  3,  3,  3,  3,  3,  3,  3,
		 3,  3,  3,  3,  3,
	};
	constexpr static UInt16 num[] = {
		     0,      0, 0x8000, 0xE6A9, 0x4000, 0x3D09, 0xB640, 0x41A7,
		0x8000, 0xE6A9, 0x2710, 0x3931, 0x5100, 0x6F91, 0x9610, 0xC5C1,
		0x1000, 0x1331, 0x16C8, 0x1ACB, 0x1F40, 0x242D, 0x2998, 0x2F87,
		0x3600, 0x3D09, 0x44A8, 0x4CE3, 0x55C0, 0x5F45, 0x6978, 0x745F,
		0x8000, 0x8C61, 0x9988, 0xA77B, 0xB640,
	};
};

template<>
struct BaseTraits< 32 > {
	constexpr static UInt8 chars_per_digit[] = {
		 0,  0, 31, 20, 15, 13, 12, 11,
		10, 10,  9,  9,  8,  8,  8,  8,
		 7,  7,  7,  7,  7,  7,  7,  7,
		 6,  6,  6,  6,  6,  6,  6,  6,
		 6,  6,  6,  6,  6,
	};
	constexpr static UInt32 num[] = {
				 0,          0, 0x80000000, 0xCFD41B91, 0x40000000, 0x48C27395, 0x81BF1000, 0x75DB9C97,
		0x40000000, 0xCFD41B91, 0x3B9ACA00, 0x8C8B6D2B, 0x19A10000, 0x309F1021, 0x57F6C100, 0x98C29B81,
		0x10000000, 0x18754571, 0x247DBC80, 0x3547667B, 0x4C4B4000, 0x6B5A6E1D, 0x94ACE180, 0xCAF18367,
		0x0B640000, 0x0E8D4A51, 0x1269AE40, 0x17179149, 0x1CB91000, 0x23744899, 0x2B73A840, 0x34E63B41,
		0x40000000, 0x4CFA3CC1, 0x5C13D840, 0x6D91B519, 0x81BF1000,
	};
};

static inline void fill_digits_0(Digit * D, Size length) {
	duff_device(length, [&](){ *D++ = 0; });
}

static inline void copy_digits(Digit const * S, Size length, Digit * D) {
	duff_device(length, [&](){ *D++ = *S++; });
}

template< typename TBignum >
struct BignumAlgorithm {
	static void reserve(TBignum & X, Size size) {
		size = align_size(size);
		if (X.capacity < size) {
			auto old_digits = X.digits;
			X.digits = new Digit[size];
			copy_digits(old_digits, X.length, X.digits);
			X.capacity = size;
			delete [] old_digits;
		}
	}

	static void clamp(TBignum & X) {
		for (; X.length > 0 && X.digits[X.length - 1] == 0; --X.length) {}
		if (X.length == 0) {
			X.sign = Sign::POS;
			X.length = 1;
		}
	}

	static void init(TBignum & X) {
		X.sign = Sign::POS;
		X.length = 0;
		X.capacity = 0;
		X.digits = nullptr;
	}

	static void set0(TBignum & X) {
		reserve(X, 1);
		X.sign = Sign::POS;
		X.digits[0] = 0;
		X.length = 1;
	}

	static void set_ud(TBignum & X, UDigit ud) {
		reserve(X, 1);
		X.sign = Sign::POS;
		X.digits[0] = ud;
		X.length = 1;
	}

	static void set_sd(TBignum & X, SDigit sd) {
		reserve(X, 1);
		if (sd < 0) {
			X.sign = Sign::NEG;
			sd = -sd;
		} else {
			X.sign = Sign::POS;
		}
		X.digits[0] = sd;
		X.length = 1;
	}

	static void set_power2(TBignum & X, Size n) {
		auto const bn = n % BITS_PER_DIGIT;
		auto const dn = n / BITS_PER_DIGIT;
		reserve(X, dn + 1);
		fill_digits_0(X.digits, dn);
		X.digits[dn] = 1 << bn;
		X.length = dn + 1;
		BR_ASSERT(X.digits[dn] != 0);
	}

	static void copy(TBignum & X, TBignum const & Y) {
		reserve(X, Y.length);
		X.sign = Y.sign;
		X.length = Y.length;
		copy_digits(Y.digits, X.capacity, X.digits);
	}

	static void copy_list(TBignum & X, std::initializer_list<Digit> L) {
		reserve(X, L.size());
		X.length = 0;
		for (Digit d : L) {
			X.digits[X.length++] = d;
		}
		clamp(X);
	}

	static void fake(TBignum & X, Digit * ds, Size length) {
		X.sign = Sign::POS;
		X.capacity = X.length = length;
		X.digits = ds;
	}

	static void fake_d(TBignum & X, Digit & d) {
		X.sign = Sign::POS;
		X.capacity = X.length = 1;
		X.digits = &d;
	}

	static void clear(TBignum & X) {
		delete [] X.digits;
		X.length = 0;
		X.capacity = 0;
		X.digits = nullptr;
	}

	static Size count_bits(TBignum const & X) {
		return X.length * BITS_PER_DIGIT - count_leading_zeros(X.digits[X.length - 1]);
	}

	static void swap(TBignum & X, TBignum & Y) {
		using BR::swap;
		swap(X.sign    , Y.sign    );
		swap(X.length  , Y.length  );
		swap(X.capacity, Y.capacity);
		swap(X.digits  , Y.digits  );
	}

	static Relation cmp(TBignum const & X, TBignum const & Y) {
		if (X.sign == Y.sign) {
			return X.sign == Sign::POS ? cmpu(X, Y) : cmpu(Y, X);
		} else {
			return X.sign == Sign::POS ? Relation::GT : Relation::LT;
		}
	}

	static Relation cmpu(TBignum const & X, TBignum const & Y) {
		if (X.length < Y.length) { return Relation::LT; }
		if (Y.length < X.length) { return Relation::GT; }

		auto xds = X.digits + X.length;
		auto yds = Y.digits + Y.length;

		Size i = X.length;
		for (; i-- > 0 && *--xds == *--yds;) {}

		return i != Size(-1) ? (*xds < *yds ? Relation::LT : Relation::GT) : Relation::EQ;
	}

	static bool is0(TBignum const & X) {
		return X.length == 1 && X.digits[0] == 0;
	}

	static void pos(TBignum & X) {
		X.sign = +X.sign;
	}

	static void neg(TBignum & X) {
		X.sign = -X.sign;
	}

	static void abs(TBignum & X) {
		X.sign = Bignum::Sign::POS;
	}

	static void conj(TBignum & X) {
		X.sign = ~X.sign;
		auto xds = X.digits;
		duff_device(X.length, [&xds](){ *xds = ~*xds; ++xds; });
	}

	static void add(TBignum const & X, TBignum const & Y, TBignum & Z) {
		if (X.sign == Y.sign) {
			if (X.length < Y.length) {
				Z.sign = X.sign; add_u(Y, X, Z);
			} else {
				Z.sign = X.sign; add_u(X, Y, Z);
			}
		} else {
			if (cmpu(X, Y) == Relation::LT) {
				Z.sign = -X.sign; sub_u(Y, X, Z);
			} else {
				Z.sign = +X.sign; sub_u(X, Y, Z);
			}
		}
	}

	static void sub(TBignum const & X, TBignum const & Y, TBignum & Z) {
		if (X.sign != Y.sign) {
			if (X.length < Y.length) {
				Z.sign = X.sign; add_u(Y, X, Z);
			} else {
				Z.sign = X.sign; add_u(X, Y, Z);
			}
		} else {
			if (cmpu(X, Y) == Relation::LT) {
				Z.sign = -X.sign; sub_u(Y, X, Z);
			} else {
				Z.sign = +X.sign; sub_u(X, Y, Z);
			}
		}
	}

	static void add_u(TBignum const & X, TBignum const & Y, TBignum & Z) {
		BR_ASSERT(X.length >= Y.length);

		auto const xlength = X.length;
		auto const ylength = Y.length;
		auto const zlength = xlength + 1;

		reserve(Z, zlength);

		auto xds = X.digits;
		auto yds = Y.digits;
		auto zds = Z.digits;

		UDDigit t = 0;
		Size i = 0;
		for (; i < ylength; ++i) {
			t += UDDigit(*xds++) + *yds++;
			*zds++ = mod_radix(t);
			t = div_radix(t);
		}
		for (; i < xlength; ++i) {
			t += UDDigit(*xds++);
			*zds++ = mod_radix(t);
			t = div_radix(t);
		}
		*zds++ = mod_radix(t);

		Z.length = zlength;
		clamp(Z);
	}

	static void sub_u(TBignum const & X, TBignum const & Y, TBignum & Z) {
		BR_ASSERT(X.length >= Y.length);

		auto const xlength = X.length;
		auto const ylength = Y.length;
		auto const zlength = xlength;

		reserve(Z, zlength);

		auto xds = X.digits;
		auto yds = Y.digits;
		auto zds = Z.digits;

		SDDigit t = 0;
		Size i = 0;
		for (; i < ylength; ++i) {
			t += SDDigit(*xds++) - *yds++;
			*zds++ = mod_radix(t);
			t = div_radix(t);
		}
		for (; i < xlength; ++i) {
			t += SDDigit(*xds++);
			*zds++ = mod_radix(t);
			t = div_radix(t);
		}

		Z.length = zlength;
		clamp(Z);
	}

	static void mul(TBignum const & X, TBignum const & Y, TBignum & Z) {
		constexpr static auto base = [](TBignum const & X, TBignum const & Y, TBignum & Z) {
			auto const xlength = X.length;
			auto const ylength = Y.length;
			auto const tlength = xlength + ylength;

			TBignum T; init(T); reserve(T, tlength); fill_digits_0(T.digits, tlength);

			for (auto xi = 0U; xi < xlength; ++xi) {
				auto yds = Y.digits;
				auto tds = T.digits + xi;

				auto const xd = UDDigit(X.digits[xi]);
				UDDigit t = 0;
				for (auto yi = ylength; yi-- > 0;) {
					t += *tds + xd * *yds++;
					*tds++ = mod_radix(t);
					t = div_radix(t);
				}
				*tds++ = mod_radix(t);
			}

			T.length = tlength;
			clamp(T);

			swap(T, Z);

			clear(T);
		};
		constexpr static auto karatsuba = [](TBignum const & X, TBignum const & Y, TBignum & Z) {
			/*
			 *  https://en.wikipedia.org/wiki/Karatsuba_multiplication
			 *
			 *  X(B) = X1 * B + X0
			 *  Y(B) = Y1 * B + Y0
			 *  Z(B) = X(B) * Y(B) = Z2 * B^2 + Z1 * B + Z0
			 *
			 *  Z0 = X0 * Y0
			 *  Z1 = X1 * Y0 + X0 * Y1 = (X1 + X0) * (Y1 + Y0) - Z2 - Z0
			 *  Z2 = X1 * Y1
			 */
			auto const xlength = X.length, ylength = Y.length;
			auto const blength = (xlength < ylength ? xlength : ylength) / 2;

			TBignum X0; fake(X0, X.digits, blength); clamp(X0);
			TBignum Y0; fake(Y0, Y.digits, blength); clamp(Y0);

			TBignum X1; fake(X1, X.digits + blength, xlength - blength);
			TBignum Y1; fake(Y1, Y.digits + blength, ylength - blength);

			TBignum Z0; init(Z0); mul(X0, Y0, Z0); // Z0 <- X0 * Y0
			TBignum Z2; init(Z2); mul(X1, Y1, Z2); // Z2 <- X1 * Y1

			TBignum TX; init(TX); add_u(X1, X0, TX); // TX <- X1 + X0
			TBignum TY; init(TY); add_u(Y1, Y0, TY); // TY <- Y1 + Y0

			TBignum & Z1 = TX; mul(TX, TY, Z1); sub(Z1, Z0, Z1); sub(Z1, Z2, Z1); // Z1 <- (TX * TY) - Z0 - Z2

			// Z <- (Z2 * B + Z1) * B + Z0
			BR_ASSERT(Z0.sign == Sign::POS);
			BR_ASSERT(Z1.sign == Sign::POS);
			BR_ASSERT(Z2.sign == Sign::POS);

			TBignum & T = Z2;
			reserve(Z, xlength + ylength);
			lsh_d(T, blength, T); add_u(T, Z1, T);
			lsh_d(T, blength, T); add_u(T, Z0, Z);

			clear(Z0); clear(Z2);
			clear(TX); clear(TY);
		};
		constexpr static auto toom3 = [](TBignum const & X, TBignum const & Y, TBignum & Z) {
			/*
			 *  https://en.wikipedia.org/wiki/Toom%E2%80%93Cook_multiplication
			 *
			 *  X(B) = X2 * B^2 + X1 * B + X0
			 *  Y(B) = Y2 * B^2 + Y1 * B + Y0
			 *  Z(B) = X(B) * Y(B) = Z4 * B^4 + Z3 * B^3 + Z2 * B^2 + Z1 * B + Z0
			 *
			 *  Z0 = X0 * Y0
			 *  Z1 = X1 * Y0 + X0 * Y1
			 *  Z2 = X0 * Y2 + X1 * Y1 + X2 * Y0
			 *  Z3 = X1 * Y2 + X2 * Y1
			 *  Z4 = X2 * Y2
			 *
			 *  Z(0)   = X(0)   * Y(0)   = X0 * Y0
			 *  Z(1)   = X(1)   * Y(1)   = (X2 + X1 + X0) * (Y2 + Y1 + Y0)
			 *  Z(-1)  = X(-1)  * Y(-1)  = (X2 - X1 + X0) * (Y2 - Y1 + Y0)
			 *  Z(-2)  = X(-2)  * Y(-2)  = (4*X2 - 2*X1 + X0) * (4*Y2 - 2*Y1 + Y0)
			 *  Z(inf) = X(inf) * Y(inf) = X2 * Y2
			 *
			 *  [Z(0)  ]   [ 1  0  0  0  0] [Z0]
			 *  [Z(1)  ]   [ 1  1  1  1  1] [Z1]
			 *  [Z(-1) ] = [ 1 -1  1 -1  1] [Z2]
			 *  [Z(-2) ]   [ 1 -2  4 -8 16] [Z3]
			 *  [Z(inf)]   [ 0  0  0  0  1] [Z4]
			 */
			auto const xlength = X.length, ylength = Y.length;
			auto const blength = (xlength < ylength ? xlength : ylength) / 3;

			// {Step1} Splitting
			TBignum X0; fake(X0, X.digits, blength); clamp(X0);
			TBignum Y0; fake(Y0, Y.digits, blength); clamp(Y0);

			TBignum X1; fake(X1, X.digits + blength, blength); clamp(X1);
			TBignum Y1; fake(Y1, Y.digits + blength, blength); clamp(Y1);

			TBignum X2; fake(X2, X.digits + 2 * blength, xlength - 2 * blength);
			TBignum Y2; fake(Y2, Y.digits + 2 * blength, ylength - 2 * blength);

			// {Step2} Evaluation
			TBignum TX1; init(TX1);
			TBignum TY1; init(TY1);
			TBignum TX2; init(TX2);
			TBignum TY2; init(TY2);
			TBignum TX3; init(TX3);
			TBignum TY3; init(TY3);

			add_u(X2, X0, TX1); // TX1 <- X2 + X0
			add_u(Y2, Y0, TY1); // TY1 <- Y2 + Y0

			sub(TX1, X1, TX2); // TX2 <- TX1 - X1 = X(-1)
			sub(TY1, Y1, TY2); // TY2 <- TY1 - Y1 = Y(-1)

			add_u(TX1, X1, TX1); // TX1 <- TX1 + X1 = X(1)
			add_u(TY1, Y1, TY1); // TY1 <- TY1 + Y1 = Y(1)

			add(TX2, X2, TX3); mul2(TX3, TX3); sub(TX3, X0, TX3); // TX3 <- (Tx2 + X2) * 2 - X0 = X(-2)
			add(TY2, Y2, TY3); mul2(TY3, TY3); sub(TY3, Y0, TY3); // TY3 <- (TY2 + Y2) * 2 - X0 = Y(-2)

			// {Step3} Pointwise multiplication
			TBignum W0; init(W0); mul( X0,  Y0, W0); // W0 <-  X0 *  Y0 = Z(0)   = [ 1  0  0  0  0]
			TBignum W1; init(W1); mul(TX1, TY1, W1); // W1 <- TX1 * TY1 = Z(1)   = [ 1  1  1  1  1]
			TBignum W2; init(W2); mul(TX2, TY2, W2); // W2 <- TX2 * TY2 = Z(-1)  = [ 1 -1  1 -1  1]
			TBignum W3; init(W3); mul(TX3, TY3, W3); // W3 <- TX3 * TY3 = Z(-2)  = [ 1 -2  4 -8 16]
			TBignum W4; init(W4); mul( X2,  Y2, W4); // W4 <-  X2 *  Y2 = Z(inf) = [ 0  0  0  0  1]

			// {Step4} Interpolation
			TBignum & Z0 = W0; // Z0 <- W0 = [ 1  0  0  0  0]
			TBignum & Z1 = W1;
			TBignum & Z2 = W2;
			TBignum & Z3 = W3;
			TBignum & Z4 = W4; // Z4 <- W4 = [ 0  0  0  0  1]

			sub(W3, W1, Z3); div_d(Z3, 3, Z3); // Z3 <- (W3 - W1) / 3 = [ 0 -1  1 -3  5]

			sub(W1, W2, Z1); div2(Z1, Z1); // Z1 <- (W1 - W2) / 2 = [ 0  1  0  1  0]

			sub(W2, W0, Z2); // Z2 <- (W2 - W0) = [ 0 -1  1 -1  1]

			sub(Z2, Z3, Z3); div2(Z3, Z3); add(Z3, Z4, Z3); add(Z3, Z4, Z3); // Z3 <- (Z2 - Z3) / 2 + Z4 + Z4 = [ 0  0  0  1  0]

			add(Z2, Z1, Z2); sub(Z2, Z4, Z2); // Z2 <- Z2 + Z1 - Z4 = [ 0  0  1  0  0]

			sub(Z1, Z3, Z1); // Z1 <- Z1 - Z3 = [ 0  1  0  0  0]

			// {Step5} Recomposition
			// Z <- (((Z4 * B + Z3) * B + Z2) * B + Z1) * B + Z0
			BR_ASSERT(W0.sign == Sign::POS);
			BR_ASSERT(W1.sign == Sign::POS);
			BR_ASSERT(W2.sign == Sign::POS);
			BR_ASSERT(W3.sign == Sign::POS);
			BR_ASSERT(W4.sign == Sign::POS);

			TBignum & T = Z4;
			reserve(Z, xlength + ylength);
			lsh_d(T, blength, T); add_u(T, Z3, T);
			lsh_d(T, blength, T); add_u(T, Z2, T);
			lsh_d(T, blength, T); add_u(T, Z1, T);
			lsh_d(T, blength, T); add_u(T, Z0, Z);

			// {Clear}
			clear(TX1); clear(TX2); clear(TX3);
			clear(TY1); clear(TY2); clear(TY3);

			clear(W0); clear(W1); clear(W2); clear(W3); clear(W4);
		};

		auto const xlength = X.length;
		auto const ylength = Y.length;
		auto const min_length = xlength < ylength ? xlength : ylength;
		auto const zsign = X.sign * Y.sign;

		if (min_length >= MUL_DOOR_TOOM) {
			toom3(X, Y, Z);
		} else if (min_length >= MUL_DOOR_KARATSUBA) {
			karatsuba(X, Y, Z);
		} else {
			base(X, Y, Z);
		}

		Z.sign = zsign;
	}

	static void div(TBignum const & X, TBignum const & Y, TBignum & Z) {
		div_mod(X, Y, &Z, (TBignum *)(nullptr));
	}

	static void mod(TBignum const & X, TBignum const & Y, TBignum & Z) {
		div_mod(X, Y, (TBignum *)(nullptr), &Z);
	}

	static void div_mod(TBignum const & X, TBignum const & Y, TBignum * Q, TBignum * R) {
		if (is0(Y)) {
			throw;
		}
		if (cmpu(X, Y) == Relation::LT) {
			if (Q != nullptr) {
				set0(*Q);
			}
			if (R != nullptr) {
				copy(*R, X);
			}
			return;
		}

		auto const qsign = X.sign * Y.sign;

		TBignum TQ; init(TQ);

		auto const tqlength = X.length - Y.length + 1;
		reserve(TQ, tqlength);

		auto tqds = TQ.digits + tqlength;

		TBignum TX; init(TX); copy(TX, X); abs(TX);
		TBignum TY; init(TY); copy(TY, Y); abs(TY);

		auto const norm = count_leading_zeros(TY.digits[TY.length-1]);

		lsh_b(TX, norm, TX);
		lsh_b(TY, norm, TY);

		auto const lx = TX.length - 1, ly = TY.length - 1;
		lsh_d(TY, lx - ly, TY);
		*--tqds = 0;
		for (; cmp(TX, TY) != Relation::LT;) {
			++*tqds;
			sub(TX, TY, TX);
		}
		rsh_d(TY, lx - ly, TY);

		TBignum T1; init(T1); reserve(T1, 3);
		TBignum T2; init(T2); reserve(T2, 2);

		for (auto i = lx; i > ly; --i) {
			auto const j = i - ly - 1;
			if (i > TX.length) {
				*--tqds = 0;
			} else {
				DDigit tqd;
				if (TX.digits[i] == TY.digits[ly]) {
					tqd = RADIX - 1;
				} else {
					auto t = ((UDDigit(TX.digits[i]) << BITS_PER_DIGIT) | TX.digits[i-1]) / TY.digits[ly];
					tqd = t >= RADIX ? RADIX - 1 : t;
				}
				++tqd;

				do {
					--tqd;
					T1.digits[0] = i > 1 ? TX.digits[i - 2] : 0;
					T1.digits[1] = i > 0 ? TX.digits[i - 1] : 0;
					T1.digits[2] = TX.digits[i];
					T1.length = 3;

					T2.digits[0] = ly > 0 ? TY.digits[ly - 1] : 0;
					T2.digits[1] = TY.digits[ly];
					T2.length = 2;
					mul_d(T2, Digit(tqd), T2);
				} while (cmpu(T1, T2) == Relation::LT);

				mul_d(TY, Digit(tqd), T1);
				lsh_d(T1, j, T1);
				sub(TX, T1, TX);

				if (TX.sign == Sign::NEG) {
					lsh_d(TY, j, T1);
					add(TX, T1, TX);
					--tqd;
				}

				*--tqds = tqd;
			}
		}

		TQ.length = tqlength;

		if (Q != nullptr) {
			TQ.length = tqlength;
			clamp(TQ);
			swap(*Q, TQ);
			Q->sign = qsign;
		}

		if (R != nullptr) {
			TX.sign = is0(TX) ? Sign::POS : X.sign;
			rsh_b(TX, norm, TX);
			swap(*R, TX);
		}

		clear(TQ);
		clear(TX);
		clear(TY);
		clear(T1);
		clear(T2);
	}

	static void bor(TBignum const & X, TBignum const & Y, TBignum & Z) {
		constexpr static auto imp = [](TBignum const & X, TBignum const & Y, TBignum & Z) {
			BR_ASSERT(X.length >= Y.length);

			auto const xlength = X.length;
			auto const ylength = Y.length;
			auto const zlength = xlength;

			reserve(Z, zlength);

			auto xds = X.digits;
			auto yds = Y.digits;
			auto zds = Z.digits;

			duff_device(          ylength, [&](){ *zds++ = *xds++ | *yds++; });
			duff_device(xlength - ylength, [&](){ *zds++ = *xds++         ; });

			BR_ASSERT((xds - X.digits) - xlength == 0);
			BR_ASSERT((yds - Y.digits) - ylength == 0);
			BR_ASSERT((zds - Z.digits) - zlength == 0);

			Z.length = zlength;
			clamp(Z);
		};
		if (X.length < Y.length) {
			imp(Y, X, Z);
		} else {
			imp(X, Y, Z);
		}
	}

	static void band(TBignum const & X, TBignum const & Y, TBignum & Z) {
		constexpr static auto imp = [](TBignum const & X, TBignum const & Y, TBignum & Z) {
			BR_ASSERT(X.length >= Y.length);

			auto const xlength = X.length;
			auto const ylength = Y.length;
			auto const zlength = xlength;

			reserve(Z, zlength);

			auto xds = X.digits;
			auto yds = Y.digits;
			auto zds = Z.digits;

			duff_device(          ylength, [&](){ *zds++ = *xds++ & *yds++; });
			duff_device(xlength - ylength, [&](){ *zds++ = *xds++         ; });

			BR_ASSERT((xds - X.digits) - xlength == 0);
			BR_ASSERT((yds - Y.digits) - ylength == 0);
			BR_ASSERT((zds - Z.digits) - zlength == 0);

			Z.length = zlength;
			clamp(Z);
		};

		if (X.length < Y.length) {
			imp(Y, X, Z);
		} else {
			imp(X, Y, Z);
		}
	}

	static void bxor(TBignum const & X, TBignum const & Y, TBignum & Z) {
		constexpr static auto imp = [](TBignum const & X, TBignum const & Y, TBignum & Z) {
			BR_ASSERT(X.length >= Y.length);

			auto const xlength = X.length;
			auto const ylength = Y.length;
			auto const zlength = xlength;

			reserve(Z, zlength);

			auto xds = X.digits, yds = Y.digits;
			auto zds = Z.digits;

			duff_device(          ylength, [&](){ *zds++ = *xds++ ^ *yds++; });
			duff_device(xlength - ylength, [&](){ *zds++ = *xds++         ; });

			BR_ASSERT((xds - X.digits) - xlength == 0);
			BR_ASSERT((yds - Y.digits) - ylength == 0);
			BR_ASSERT((zds - Z.digits) - zlength == 0);

			Z.length = zlength;
			clamp(Z);
		};

		if (X.length < Y.length) {
			imp(Y, X, Z);
		} else {
			imp(X, Y, Z);
		}
	}

	static void add_d(TBignum const & X, Digit d, TBignum & Z) {
		TBignum Y; fake_d(Y, d); add(X, Y, Z);
	}

	static void sub_d(TBignum const & X, Digit d, TBignum & Z) {
		TBignum Y; fake_d(Y, d); sub(X, Y, Z);
	}

	static void mul_d(TBignum const & X, Digit d, TBignum & Z) {
		auto const xlength = X.length;
		auto const zlength = xlength + 1;

		reserve(Z, zlength);

		auto xds = X.digits;
		auto zds = Z.digits;

		UDDigit t = 0;
		for (auto xi = xlength; xi-- > 0;) {
			t += UDDigit(*xds++) * d;
			*zds++ = mod_radix(t);
			t = div_radix(t);
		}
		*zds++ = mod_radix(t);

		Z.sign   = X.sign;
		Z.length = zlength;
		clamp(Z);
	}

	static void div_d(TBignum const & X, Digit d, TBignum & Z) {
		auto const xlength = X.length;
		auto const zlength = xlength;

		reserve(Z, zlength);

		auto xds = X.digits + xlength;
		auto zds = Z.digits + zlength;

		UDDigit t = 0;
		Digit w;
		for (auto xi = xlength; xi-- > 0;) {
			t = (t << BITS_PER_DIGIT) | *--xds;
			if (t < d) {
				w = 0;
			} else {
				w = t / d;
				t %= d;
			}
			*--zds = w;
		}

		Z.sign   = X.sign;
		Z.length = zlength;
		clamp(Z);
	}

	static Digit mod_d(TBignum const & X, Digit d) {
		auto const xlength = X.length;

		auto xds = X.digits + xlength;

		UDDigit t = 0;
		Digit w;
		for (auto xi = xlength; xi-- > 0;) {
			t = (t << BITS_PER_DIGIT) | *--xds;
			if (t < d) {
				w = 0;
			} else {
				w = Digit(t / d);
				t %= d;
			}
		}

		return Digit(t);
	}

	static Digit div_mod_d(TBignum const & X, Digit d, TBignum & Z) {
		auto const xlength = X.length;
		auto const zlength = xlength;

		reserve(Z, zlength);

		auto xds = X.digits + xlength;
		auto zds = Z.digits + zlength;

		UDDigit t = 0;
		Digit w;
		for (auto xi = xlength; xi-- > 0;) {
			t = (t << BITS_PER_DIGIT) | *--xds;
			if (t < d) {
				w = 0;
			} else {
				w = Digit(t / d);
				t %= d;
			}
			*--zds = w;
		}

		Z.sign   = X.sign;
		Z.length = zlength;
		clamp(Z);

		return Digit(t);
	}

	static void bor_d(TBignum const & X, Digit d, TBignum & Z) {
		TBignum Y; fake_d(Y, d); bor(X, Y, Z);
	}

	static void band_d(TBignum const & X, Digit d, TBignum & Z) {
		TBignum Y; fake_d(Y, d); band(X, Y, Z);
	}

	static void bxor_d(TBignum const & X, Digit d, TBignum & Z) {
		TBignum Y; fake_d(Y, d); bxor(X, Y, Z);
	}

	static void sqr(TBignum const & X, TBignum & Z) {
		constexpr static auto base = [](TBignum const & X, TBignum & Z) {
			auto const xlength = X.length;
			auto const tlength = xlength + xlength + 1;

			TBignum T; init(T); reserve(T, tlength); fill_digits_0(T.digits, tlength);

			for (auto xi = 0U; xi < xlength; ++xi) {
				auto const xdi = UDDigit(X.digits[xi]);
				auto const xdh = div_radix(xdi * 2);
				auto const xdl = mod_radix(xdi * 2);

				UDDigit t = T.digits[xi + xi] + xdi * xdi;
				T.digits[xi + xi] = mod_radix(t);
				t = div_radix(t);

				for (auto xj = xi + 1; xj < xlength; ++xj) {
					auto const xdj = UDDigit(X.digits[xj]);
					t += T.digits[xi + xj] + xdl * xdj;
					T.digits[xi + xj] = mod_radix(t);
					t = div_radix(t) + xdh * xdj;
				}

				t += T.digits[xi + xlength];
				T.digits[xi + xlength] = mod_radix(t);
				T.digits[xi + xlength + 1] += mod_radix(div_radix(t));
			}

			T.length = tlength;
			clamp(T);
			swap(T, Z);
			clear(T);
		};
		constexpr static auto karatsuba = [](TBignum const & X, TBignum & Z) {
			/*
			 * https://en.wikipedia.org/wiki/Karatsuba_multiplication
			 *
			 * X(B) = X1 * B + X
			 * Z(B) = X(B)^2 = Z2 * B^2 + Z1 * B + Z0
			 *
			 * Z0 = X0^2
			 * Z1 = 2 * X1 * X0 = (X1 + X0)^2 - Z2 - Z0
			 * Z2 = X1^2
			 */
			auto const xlength = X.length;
			auto const blength = xlength / 2;

			TBignum X0; fake(X0, X.digits, blength); clamp(X0);

			TBignum X1; fake(X1, X.digits + blength, xlength - blength);

			TBignum Z0; init(Z0); sqr(X0, Z0); // Z0 <- X0^2
			TBignum Z2; init(Z2); sqr(X1, Z2); // Z2 <- X1^2

			TBignum TX; init(TX); add_u(X1, X0, TX); // TX <- X1 + X0

			TBignum & Z1 = TX; sqr(TX, Z1); sub(Z1, Z0, Z1); sub(Z1, Z2, Z1); // Z1 <- TX^2 - Z0 - Z2

			// Z <- (Z2 * B + Z1) * B + Z0
			BR_ASSERT(Z0.sign == Bignum::Sign::POS);
			BR_ASSERT(Z1.sign == Bignum::Sign::POS);
			BR_ASSERT(Z2.sign == Bignum::Sign::POS);

			TBignum & T = Z2; reserve(Z, xlength + xlength);

			lsh_d(T, blength, T); add_u(T, Z1, T);
			lsh_d(T, blength, T);add_u(T, Z0, Z);

			clear(Z0); clear(Z2); clear(TX);
		};
		constexpr static auto toom3 = [](TBignum const & X, TBignum & Z) {
			/*
			 * https://en.wikipedia.org/wiki/Toom%E2%80%93Cook_multiplication
			 *
			 * X(B) = X2 * B^2 + X1 * B + X0
			 * Z(B) = X(B)^2 = Z4 * B^4 + Z3 * B^3 + Z2 * B^2 + Z1 * B + Z0
			 *
			 * Z0 = X0^2
			 * Z1 = 2 * X1 * X0
			 * Z2 = 2 * X0 * X2 + X1^2
			 * Z3 = 2 * X1 * X2
			 * Z4 = X2^2
			 *
			 * Z(0)   = X(0)^2   = X0^2
			 * Z(1)   = X(1)^2   = (X2 + X1 + X0)^2
			 * Z(-1)  = X(-1)^2  = (X2 - X1 + X0)^2
			 * Z(-2)  = X(-2)^2  = (4*X2 - 2*X1 + X0)^2
			 * Z(inf) = X(inf)^2 = X2^2
			 *
			 * [Z(0)  ]   [ 1  0  0  0  0] [Z0]
			 * [Z(1)  ]   [ 1  1  1  1  1] [Z1]
			 * [Z(-1) ] = [ 1 -1  1 -1  1] [Z2]
			 * [Z(-2) ]   [ 1 -2  4 -8 16] [Z3]
			 * [Z(inf)]   [ 0  0  0  0  1] [Z4]
			 */
			auto const xlength = X.length;
			auto const blength = xlength / 3;

			// {Step1} Splitting
			TBignum X0; fake(X0, X.digits, blength); clamp(X0);

			TBignum X1; fake(X1, X.digits + blength, blength); clamp(X1);

			TBignum X2; fake(X2, X.digits + 2 * blength, xlength - 2 * blength);

			// {Step2} Evaluation
			TBignum TX1; init(TX1);
			TBignum TX2; init(TX2);
			TBignum TX3; init(TX3);

			add_u(X2, X0, TX1); // TX1 <- X2 + X0

			sub(TX1, X1, TX2); // TX2 <- TX1 - X1 = X(-1)

			add_u(TX1, X1, TX1); // TX1 <- TX1 + X1 = X(1)

			add(TX2, X2, TX3); mul2(TX3, TX3); sub(TX3, X0, TX3); // TX3 <- (Tx2 + X2) * 2 - X0 = X(-2)

			// {Step3} Pointwise multiplication
			TBignum W0; init(W0); sqr( X0, W0); // W0 <-  X0^2 = Z(0)   = [ 1  0  0  0  0]
			TBignum W1; init(W1); sqr(TX1, W1); // W1 <- TX1^2 = Z(1)   = [ 1  1  1  1  1]
			TBignum W2; init(W2); sqr(TX2, W2); // W2 <- TX2^2 = Z(-1)  = [ 1 -1  1 -1  1]
			TBignum W3; init(W3); sqr(TX3, W3); // W3 <- TX3^2 = Z(-2)  = [ 1 -2  4 -8 16]
			TBignum W4; init(W4); sqr( X2, W4); // W4 <-  X2^2 = Z(inf) = [ 0  0  0  0  1]

			// {Step4} Interpolation
			TBignum & Z0 = W0; // Z0 <- W0 = [ 1  0  0  0  0]
			TBignum & Z1 = W1;
			TBignum & Z2 = W2;
			TBignum & Z3 = W3;
			TBignum & Z4 = W4; // Z4 <- W4 = [ 0  0  0  0  1]

			sub(W3, W1, Z3); div_d(Z3, 3, Z3); // Z3 <- (W3 - W1) / 3 = [ 0 -1  1 -3  5]

			sub(W1, W2, Z1); div2(Z1, Z1); // Z1 <- (W1 - W2) / 2 = [ 0  1  0  1  0]

			sub(W2, W0, Z2); // Z2 <- (W2 - W0) = [ 0 -1  1 -1  1]

			sub(Z2, Z3, Z3); div2(Z3, Z3); add(Z3, Z4, Z3); add(Z3, Z4, Z3); // Z3 <- (Z2 - Z3) / 2 + Z4 + Z4 = [ 0  0  0  1  0]

			add(Z2, Z1, Z2); sub(Z2, Z4, Z2); // Z2 <- Z2 + Z1 - Z4 = [ 0  0  1  0  0]

			sub(Z1, Z3, Z1); // Z1 <- Z1 - Z3 = [ 0  1  0  0  0]

			// {Step5} Recomposition
			// Z <- (((Z4 * B + Z3) * B + Z2) * B + Z1) * B + Z0
			BR_ASSERT(Z0.sign == Bignum::Sign::POS);
			BR_ASSERT(Z1.sign == Bignum::Sign::POS);
			BR_ASSERT(Z2.sign == Bignum::Sign::POS);
			BR_ASSERT(Z3.sign == Bignum::Sign::POS);
			BR_ASSERT(Z4.sign == Bignum::Sign::POS);

			TBignum & T = Z4; reserve(Z, xlength + xlength);

			lsh_d(T, blength, T); add_u(T, Z3, T);
			lsh_d(T, blength, T); add_u(T, Z2, T);
			lsh_d(T, blength, T); add_u(T, Z1, T);
			lsh_d(T, blength, T); add_u(T, Z0, Z);

			// {Clear}
			clear(TX1); clear(TX2); clear(TX3);

			clear(W0); clear(W1); clear(W2); clear(W3); clear(W4);
		};

		auto const xlength = X.length;
		auto const zsign = X.sign * X.sign;
		if (xlength >= SQR_DOOR_TOOM) {
			toom3(X, Z);
		} else if (xlength >= SQR_DOOR_KARATSUBA) {
			karatsuba(X, Z);
		} else {
			base(X, Z);
		}
		Z.sign = zsign;
	}

	static void mul2(TBignum const & X, TBignum & Z) {
		auto const xlength = X.length;
		auto const zlength = xlength + 1;

		reserve(Z, zlength);

		auto xds = X.digits;
		auto zds = Z.digits;

		UDDigit t = 0;
		for (auto xi = xlength; xi-- > 0; ) {
			t |= UDDigit(*xds++) << 1;
			*zds++ = mod_radix(t);
			t = div_radix(t);
		}
		*zds++ = mod_radix(t);

		Z.sign   = X.sign;
		Z.length = zlength;
		clamp(Z);
	}

	static void div2(TBignum const & X, TBignum & Z) {
		auto const xlength = X.length;
		auto const zlength = xlength;

		reserve(Z, zlength);

		auto xds = X.digits + xlength;
		auto zds = Z.digits + zlength;

		UDDigit t = 0;
		for (auto xi = xlength; xi-- > 0; ) {
			t |= UDDigit(*--xds) << (BITS_PER_DIGIT - 1);
			*--zds = div_radix(t);
			t = mul_radix(t);
		}

		Z.sign   = X.sign;
		Z.length = zlength;
		clamp(Z);
	}

	static void lsh(TBignum const & X, Digit n, TBignum & Z) {
		auto const bn = n % BITS_PER_DIGIT;
		auto const dn = n / BITS_PER_DIGIT;

		auto const xlength = X.length, zlength = xlength + dn + 1;

		reserve(Z, zlength);

		auto xds = X.digits + xlength;
		auto zds = Z.digits + zlength;

		UDDigit t = 0;
		for (auto xi = xlength; xi-- > 0; ) {
			t |= UDDigit(*--xds) << bn;
			*--zds = div_radix(t);
			t = mul_radix(t);
		}
		*--zds = div_radix(t);

		duff_device(dn, [&](){ *--zds = 0; });

		BR_ASSERT(xds == X.digits);
		BR_ASSERT(zds == Z.digits);

		Z.sign   = X.sign;
		Z.length = zlength;
		clamp(Z);
	}

	static void rsh(TBignum const & X, Digit n, TBignum & Z) {
		auto const bn = n % BITS_PER_DIGIT;
		auto const dn = n / BITS_PER_DIGIT;

		if (dn - X.length >= 0) {
			set0(Z);
			return;
		}

		auto const xlength = X.length;
		auto const zlength = xlength - dn;

		reserve(Z, zlength);

		auto xds = X.digits + dn;
		auto zds = Z.digits;

		UDDigit t = (*xds++) >> bn;
		for (auto zi = zlength; zi-- > 1; ) {
			t |= UDDigit(*xds++) << (BITS_PER_DIGIT - bn);
			*zds++ = mod_radix(t);
			t = div_radix(t);
		}
		*zds++ = mod_radix(t);

		Z.sign   = X.sign;
		Z.length = zlength;
		clamp(Z);
	}

	static void lsh_b(TBignum const & X, Digit bn, TBignum & Z) {
		BR_ASSERT(0 <= bn && bn <= BITS_PER_DIGIT);

		auto const xlength = X.length;
		auto const zlength = xlength + 1;

		reserve(Z, zlength);

		auto xds = X.digits;
		auto zds = Z.digits;

		UDDigit t = 0;
		for (auto xi = xlength; xi-- > 0; ) {
			t |= UDDigit(*xds++) << bn;
			*zds++ = mod_radix(t);
			t = div_radix(t);
		}
		*zds++ = mod_radix(t);

		Z.sign   = X.sign;
		Z.length = zlength;
		clamp(Z);
	}

	static void rsh_b(TBignum const & X, Digit bn, TBignum & Z) {
		BR_ASSERT(bn <= BITS_PER_DIGIT);

		auto const xlength = X.length;
		auto const zlength = xlength;

		reserve(Z, zlength);

		auto xds = X.digits + xlength;
		auto zds = Z.digits + zlength;

		UDDigit t = 0;
		bn = BITS_PER_DIGIT - bn;
		for (auto xi = xlength; xi-- > 0; ) {
			t |= UDDigit(*--xds) << bn;
			*--zds = div_radix(t);
			t = mul_radix(t);
		}

		Z.sign   = X.sign;
		Z.length = zlength;
		clamp(Z);
	}

	static void lsh_d(TBignum const & X, Digit dn, TBignum & Z) {
		auto const xlength = X.length;
		auto const zlength = xlength + dn;

		reserve(Z, zlength);

		auto xds = X.digits + xlength;
		auto zds = Z.digits + zlength;

		duff_device(xlength, [&](){ *--zds = *--xds; });
		duff_device(dn, [&](){ *--zds = 0; });

		BR_ASSERT(xds == X.digits);
		BR_ASSERT(zds == Z.digits);

		Z.sign   = X.sign;
		Z.length = zlength;
	}

	static void rsh_d(TBignum const & X, Digit dn, TBignum & Z) {
		if (X.length <= dn) {
			set0(Z);
			return;
		}

		auto const xlength = X.length;
		auto const zlength = xlength - dn;

		reserve(Z, zlength);

		auto xds = X.digits + dn;
		auto zds = Z.digits;

		duff_device(zlength, [&](){ *zds++ = *xds++; });

		BR_ASSERT((xds - X.digits) - xlength == 0);
		BR_ASSERT((zds - Z.digits) - zlength == 0);

		Z.sign   = X.sign;
		Z.length = zlength;
	}

	static std::string inspect(TBignum const & X) {
		std::ostringstream oss;

		oss << to_c(X.sign) << "0x";

		for (Size i = X.length; i-- > 0;) {
			oss << std::setfill('0') << std::setw(BITS_PER_DIGIT / 4) << std::hex << X.digits[i];
		}

		return oss.str();
	}

	static std::string to_s(TBignum const & X, Digit base, bool show_plus) {
		constexpr static auto ALPHABETA = "0123456789abcdefghijklmnopqrstuvwxyz";
		static auto to_s_generic = [](TBignum const & X, Digit base) {
			std::string s;
			TBignum T; init(T); copy(T, X);
			do {
				s += ALPHABETA[div_mod_d(T, base, T)];
			} while (!is0(T));
			clear(T);
			return std::string(s.rbegin(), s.rend());
		};
		static auto to_s_power_2 = [](TBignum const & X, Digit base) {
			auto const xlength = X.length;
			auto const bits_per_char = integral_log2(base);
			auto mod_base_mask = (1 << bits_per_char) - 1;

			std::string s; s.reserve((count_bits(X) + bits_per_char) / bits_per_char);

			auto xds = X.digits + xlength;
			Digit buffer = *--xds;

			int bit_pos = BITS_PER_DIGIT - count_leading_zeros(buffer);
			if (auto t = bit_pos % bits_per_char) {
				bit_pos += bits_per_char - t;
			}

			for (auto xi = xlength - 1;;) {
				bit_pos -= bits_per_char;
				for (; bit_pos >= 0;) {
					s += ALPHABETA[(buffer >> bit_pos) & mod_base_mask];
					bit_pos -= bits_per_char;
				}
				if (xi-- <= 0) {
					break;
				}
				auto temp = (buffer << -bit_pos) & mod_base_mask;
				buffer = *--xds;
				bit_pos += BITS_PER_DIGIT;
				s += ALPHABETA[temp | (buffer >> bit_pos)];
			}

			return s;
		};

		if (base < 2 || 36 < base) {
			throw std::invalid_argument("base");
		}

		std::string s;
		if (X.sign == Sign::NEG) {
			s += '-';
		} else if (show_plus) {
			s += '+';
		}

		if (is0(X)) {
			return "0";
		} else if (is_power_of_2(base)) {
			return s + to_s_power_2(X, base);
		} else {
			return s + to_s_generic(X, base);
		}
	}

}; // struct BignumAlgorithm

template< typename TBignum >
static inline BignumAlgorithm<TBignum> algorithms(TBignum const & X) {
	return BignumAlgorithm<TBignum>();
}

} // namespace [anonymous]

Bignum const Bignum::ZERO (UDigit(0));

Bignum::Bignum() : Bignum(not_allocate_tag) { algorithms(m_imp).set0(m_imp); }

Bignum::Bignum(Bignum const &  Y) : Bignum(not_allocate_tag) { algorithms(m_imp).copy(m_imp, Y.m_imp); }
Bignum::Bignum(Bignum       && Y) : Bignum(not_allocate_tag) { algorithms(m_imp).swap(m_imp, Y.m_imp); }

Bignum::Bignum(UDigit ud) : Bignum(not_allocate_tag) { algorithms(m_imp).set_ud(m_imp, ud); }
Bignum::Bignum(SDigit sd) : Bignum(not_allocate_tag) { algorithms(m_imp).set_sd(m_imp, sd); }

Bignum::Bignum(std::initializer_list<Digit> L) : Bignum(not_allocate_tag) { algorithms(m_imp).copy_list(m_imp, L); }

Bignum::Bignum(Power2Tag, Size n) : Bignum(not_allocate_tag) { algorithms(m_imp).set_power2(m_imp, n); }

Bignum::Bignum(NotAllocateTag) { algorithms(m_imp).init(m_imp); }

Bignum::~Bignum() { algorithms(m_imp).clear(m_imp); }

Size Bignum::bit_length() const { return algorithms(m_imp).count_bits(m_imp); }

Bignum & Bignum::reserve(Size size) { algorithms(m_imp).reserve(m_imp, size); return *this; }

Bignum & Bignum::swap(Bignum & Y) { algorithms(m_imp).swap(m_imp, Y.m_imp); return *this; }

Bignum & Bignum::assign(Bignum const &  Y) { algorithms(m_imp).copy(m_imp, Y.m_imp); return *this; }
Bignum & Bignum::assign(Bignum       && Y) { algorithms(m_imp).swap(m_imp, Y.m_imp); return *this; }

Bignum & Bignum::assign(UDigit ud) { algorithms(m_imp).set_ud(m_imp, ud); return *this; }
Bignum & Bignum::assign(SDigit sd) { algorithms(m_imp).set_sd(m_imp, sd); return *this; }

Bignum & Bignum::assign(std::initializer_list<Digit> L) { algorithms(m_imp).copy_list(m_imp, L); return *this; }

Bignum & Bignum::set0() { algorithms(m_imp).set0(m_imp); return *this; }

bool Bignum::is0() const { return algorithms(m_imp).is0(m_imp); }

Relation Bignum::cmp(Bignum const & Y) const { return algorithms(m_imp).cmp(m_imp, Y.m_imp); }

Bignum & Bignum::set_pos () { algorithms(m_imp).pos (m_imp); return *this; }
Bignum & Bignum::set_neg () { algorithms(m_imp).neg (m_imp); return *this; }
Bignum & Bignum::set_abs () { algorithms(m_imp).abs (m_imp); return *this; }
Bignum & Bignum::set_conj() { algorithms(m_imp).conj(m_imp); return *this; }

Bignum Bignum::add (Bignum const & Y) const { Bignum Z(not_allocate_tag); algorithms(m_imp).add (m_imp, Y.m_imp, Z.m_imp); return Z; }
Bignum Bignum::sub (Bignum const & Y) const { Bignum Z(not_allocate_tag); algorithms(m_imp).sub (m_imp, Y.m_imp, Z.m_imp); return Z; }
Bignum Bignum::mul (Bignum const & Y) const { Bignum Z(not_allocate_tag); algorithms(m_imp).mul (m_imp, Y.m_imp, Z.m_imp); return Z; }
Bignum Bignum::div (Bignum const & Y) const { Bignum Z(not_allocate_tag); algorithms(m_imp).div (m_imp, Y.m_imp, Z.m_imp); return Z; }
Bignum Bignum::mod (Bignum const & Y) const { Bignum Z(not_allocate_tag); algorithms(m_imp).mod (m_imp, Y.m_imp, Z.m_imp); return Z; }
Bignum Bignum::bor (Bignum const & Y) const { Bignum Z(not_allocate_tag); algorithms(m_imp).bor (m_imp, Y.m_imp, Z.m_imp); return Z; }
Bignum Bignum::band(Bignum const & Y) const { Bignum Z(not_allocate_tag); algorithms(m_imp).band(m_imp, Y.m_imp, Z.m_imp); return Z; }
Bignum Bignum::bxor(Bignum const & Y) const { Bignum Z(not_allocate_tag); algorithms(m_imp).bxor(m_imp, Y.m_imp, Z.m_imp); return Z; }

Bignum & Bignum::add_by (Bignum const & Y) { algorithms(m_imp).add (m_imp, Y.m_imp, m_imp); return *this; }
Bignum & Bignum::sub_by (Bignum const & Y) { algorithms(m_imp).sub (m_imp, Y.m_imp, m_imp); return *this; }
Bignum & Bignum::mul_by (Bignum const & Y) { algorithms(m_imp).mul (m_imp, Y.m_imp, m_imp); return *this; }
Bignum & Bignum::div_by (Bignum const & Y) { algorithms(m_imp).div (m_imp, Y.m_imp, m_imp); return *this; }
Bignum & Bignum::mod_by (Bignum const & Y) { algorithms(m_imp).mod (m_imp, Y.m_imp, m_imp); return *this; }
Bignum & Bignum::bor_by (Bignum const & Y) { algorithms(m_imp).bor (m_imp, Y.m_imp, m_imp); return *this; }
Bignum & Bignum::band_by(Bignum const & Y) { algorithms(m_imp).band(m_imp, Y.m_imp, m_imp); return *this; }
Bignum & Bignum::bxor_by(Bignum const & Y) { algorithms(m_imp).bxor(m_imp, Y.m_imp, m_imp); return *this; }

Bignum Bignum::add (Digit  d) const { Bignum Z(not_allocate_tag); algorithms(m_imp).add_d (m_imp,  d, Z.m_imp); return Z; }
Bignum Bignum::sub (Digit  d) const { Bignum Z(not_allocate_tag); algorithms(m_imp).sub_d (m_imp,  d, Z.m_imp); return Z; }
Bignum Bignum::mul (Digit  d) const { Bignum Z(not_allocate_tag); algorithms(m_imp).mul_d (m_imp,  d, Z.m_imp); return Z; }
Bignum Bignum::div (Digit  d) const { Bignum Z(not_allocate_tag); algorithms(m_imp).div_d (m_imp,  d, Z.m_imp); return Z; }
Bignum Bignum::bor (Digit  d) const { Bignum Z(not_allocate_tag); algorithms(m_imp).bor_d (m_imp,  d, Z.m_imp); return Z; }
Bignum Bignum::band(Digit  d) const { Bignum Z(not_allocate_tag); algorithms(m_imp).band_d(m_imp,  d, Z.m_imp); return Z; }
Bignum Bignum::bxor(Digit  d) const { Bignum Z(not_allocate_tag); algorithms(m_imp).bxor_d(m_imp,  d, Z.m_imp); return Z; }
Bignum Bignum::lsh (Digit  n) const { Bignum Z(not_allocate_tag); algorithms(m_imp).lsh   (m_imp,  n, Z.m_imp); return Z; }
Bignum Bignum::rsh (Digit  n) const { Bignum Z(not_allocate_tag); algorithms(m_imp).rsh   (m_imp,  n, Z.m_imp); return Z; }
Bignum Bignum::lshb(Digit bn) const { Bignum Z(not_allocate_tag); algorithms(m_imp).lsh_b (m_imp, bn, Z.m_imp); return Z; }
Bignum Bignum::rshb(Digit bn) const { Bignum Z(not_allocate_tag); algorithms(m_imp).rsh_b (m_imp, bn, Z.m_imp); return Z; }
Bignum Bignum::lshd(Digit dn) const { Bignum Z(not_allocate_tag); algorithms(m_imp).lsh_d (m_imp, dn, Z.m_imp); return Z; }
Bignum Bignum::rshd(Digit dn) const { Bignum Z(not_allocate_tag); algorithms(m_imp).rsh_d (m_imp, dn, Z.m_imp); return Z; }

Bignum Bignum::mod(Digit d) const { return Bignum(BignumAlgorithm< decltype(m_imp) >::mod_d(m_imp, d)); }

Bignum & Bignum::add_by (Digit  d) { algorithms(m_imp).add_d (m_imp,  d, m_imp); return *this; }
Bignum & Bignum::sub_by (Digit  d) { algorithms(m_imp).sub_d (m_imp,  d, m_imp); return *this; }
Bignum & Bignum::mul_by (Digit  d) { algorithms(m_imp).mul_d (m_imp,  d, m_imp); return *this; }
Bignum & Bignum::div_by (Digit  d) { algorithms(m_imp).div_d (m_imp,  d, m_imp); return *this; }
Bignum & Bignum::bor_by (Digit  d) { algorithms(m_imp).bor_d (m_imp,  d, m_imp); return *this; }
Bignum & Bignum::band_by(Digit  d) { algorithms(m_imp).band_d(m_imp,  d, m_imp); return *this; }
Bignum & Bignum::bxor_by(Digit  d) { algorithms(m_imp).bxor_d(m_imp,  d, m_imp); return *this; }
Bignum & Bignum::lsh_by (Digit  n) { algorithms(m_imp).lsh   (m_imp,  n, m_imp); return *this; }
Bignum & Bignum::rsh_by (Digit  n) { algorithms(m_imp).rsh   (m_imp,  n, m_imp); return *this; }
Bignum & Bignum::lshb_by(Digit bn) { algorithms(m_imp).lsh_b (m_imp, bn, m_imp); return *this; }
Bignum & Bignum::rshb_by(Digit bn) { algorithms(m_imp).rsh_b (m_imp, bn, m_imp); return *this; }
Bignum & Bignum::lshd_by(Digit dn) { algorithms(m_imp).lsh_d (m_imp, dn, m_imp); return *this; }
Bignum & Bignum::rshd_by(Digit dn) { algorithms(m_imp).rsh_d (m_imp, dn, m_imp); return *this; }

Bignum Bignum::sqr() const { Bignum Z(not_allocate_tag); algorithms(m_imp).sqr(m_imp, Z.m_imp); return Z; }

Bignum & Bignum::set_sqr() { BignumAlgorithm< decltype(m_imp) >::sqr(m_imp, m_imp); return *this; }

Bignum Bignum::mul2() const { Bignum Z(not_allocate_tag); algorithms(m_imp).mul2(m_imp, Z.m_imp); return Z; }
Bignum Bignum::div2() const { Bignum Z(not_allocate_tag); algorithms(m_imp).div2(m_imp, Z.m_imp); return Z; }

Bignum & Bignum::mul_by2() { algorithms(m_imp).mul2(m_imp, m_imp); return *this; }
Bignum & Bignum::div_by2() { algorithms(m_imp).div2(m_imp, m_imp); return *this; }

Pair< Bignum, Bignum > Bignum::div_mod(Bignum const & Y) const {
	Bignum Q, R;
	algorithms(m_imp).div_mod(m_imp, Y.m_imp, &Q.m_imp, &R.m_imp);
	return make_pair(move(Q), move(R));
}

Pair< Bignum, Digit > Bignum::div_mod(Digit d) const {
	Bignum Q(not_allocate_tag);
	auto r = algorithms(m_imp).div_mod_d(m_imp, d, Q.m_imp);
	return make_pair(move(Q), r);
}

std::string Bignum::inspect() const {
	return algorithms(m_imp).inspect(m_imp);
}

std::string Bignum::to_s(Digit base, bool show_plus) const {
	return algorithms(m_imp).to_s(m_imp, base, show_plus);
}

} // namespace Math
} // namespace BR
