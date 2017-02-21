/**
 * @file
 * @author Bromine0x23
 * @since 1.0
 */
#include <libbr/math/bignum.hpp>

#include <libbr/assert/assert.hpp>
#include <libbr/exception/argument_exception.hpp>
#include <libbr/utility/duff_device.hpp>
#include <sstream>
#include <iomanip>

namespace BR {

namespace {

inline void fill_digits_0(BignumConfig::Digit * D, BignumConfig::Size length) {
	duff_device(length, [&](){ *D++ = 0; });
}

inline void copy_digits(BignumConfig::Digit const * S, BignumConfig::Size length, BignumConfig::Digit * D) {
	duff_device(length, [&](){ *D++ = *S++; });
}

} // namespace [Anonymous]

void BignumAlgorithm::reserve(BignumData & X, Size size) {
	size = align_size(size);
	if (capacity(X) < size) {
		auto old_digits = X.digits;
		digits(X) = new Digit[size];
		copy_digits(old_digits, length(X), digits(X));
		capacity(X) = size;
		delete [] old_digits;
	}
}

void BignumAlgorithm::clamp(BignumData & X) {
	for (auto & xlength = length(X); xlength > 0 && digits(X)[xlength - 1] == 0; --xlength) {}
	if (length(X) == 0) {
		sign(X) = Sign::ZPOS;
		length(X) = 1;
	}
}

void BignumAlgorithm::set_power2(BignumData & X, UDigit n) {
	auto const bn = n % BIT_PER_DIGIT;
	auto const dn = n / BIT_PER_DIGIT;
	reserve(X, dn + 1);
	fill_digits_0(digits(X), dn);
	digits(X)[dn] = Digit(1 << bn);
	length(X)= dn + 1;
	BR_ASSERT(digits(X)[dn] != 0);
}

void BignumAlgorithm::copy(BignumData & X, BignumData const & Y) {
	reserve(X, length(Y));
	sign(X) = sign(Y);
	length(X) = length(Y);
	copy_digits(digits(Y), capacity(X), digits(X));
}

Relation BignumAlgorithm::cmp_u(BignumData const & X, BignumData const & Y) {
	if (length(X) < length(Y)) {
		return Relation::LT;
	}

	if (length(Y) < length(X)) {
		return Relation::GT;
	}

	auto xds = digits(X) + length(X);
	auto yds = digits(Y) + length(X);

	Size i = length(X);
	for (; i-- > 0 && *--xds == *--yds;) {}

	return i != Size(-1) ? (*xds < *yds ? Relation::LT : Relation::GT) : Relation::EQ;
}

void BignumAlgorithm::conj(BignumData & X) {
	sign(X) = ~sign(X);
	auto xds = digits(X);
	duff_device(length(X), [&xds](){ *xds = ~*xds; ++xds; });
}

void BignumAlgorithm::add_u(BignumData const & X, BignumData const & Y, BignumData & Z) {
	auto const xlength = length(X);
	auto const ylength = length(Y);
	auto const zlength = xlength + 1;

	BR_ASSERT(xlength >= ylength);

	reserve(Z, zlength);

	auto xds = digits(X);
	auto yds = digits(Y);
	auto zds = digits(Z);

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

	BR_ASSERT((xds - digits(X)) - xlength == 0);
	BR_ASSERT((yds - digits(Y)) - ylength == 0);
	BR_ASSERT((zds - digits(Z)) - zlength == 0);

	length(Z) = zlength;
	clamp(Z);
}

void BignumAlgorithm::sub_u(BignumData const & X, BignumData const & Y, BignumData & Z) {
	auto const xlength = length(X);
	auto const ylength = length(Y);
	auto const zlength = xlength;

	BR_ASSERT(xlength >= ylength);

	reserve(Z, zlength);

	auto xds = digits(X);
	auto yds = digits(Y);
	auto zds = digits(Z);

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

	BR_ASSERT((xds - digits(X)) - xlength == 0);
	BR_ASSERT((yds - digits(Y)) - ylength == 0);
	BR_ASSERT((zds - digits(Z)) - zlength == 0);

	length(Z) = zlength;
	clamp(Z);
}

void BignumAlgorithm::mul(BignumData const & X, BignumData const & Y, BignumData & Z) {
	static const auto base = [](BignumData const & X, BignumData const & Y, BignumData & Z) {
		auto const xlength = length(X);
		auto const ylength = length(Y);
		auto const tlength = xlength + ylength;

		BignumData T; init(T); reserve(T, tlength); fill_digits_0(T.digits, tlength);

		for (auto xi = 0U; xi < xlength; ++xi) {
			auto yds = digits(Y);
			auto tds = digits(T) + xi;

			auto const xd = UDDigit(X.digits[xi]);
			UDDigit t = 0;
			for (auto yi = ylength; yi-- > 0;) {
				t += *tds + xd * *yds++;
				*tds++ = mod_radix(t);
				t = div_radix(t);
			}
			*tds++ = mod_radix(t);
		}

		length(T) = tlength;
		clamp(T);

		swap(T, Z);

		clear(T);
	};
	static const auto karatsuba = [](BignumData const & X, BignumData const & Y, BignumData & Z) {
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
		auto const xlength = length(X);
		auto const ylength = length(Y);
		auto const blength = (xlength < ylength ? xlength : ylength) / 2;

		BignumData X0; fake(X0, digits(X), blength); clamp(X0);
		BignumData Y0; fake(Y0, digits(Y), blength); clamp(Y0);

		BignumData X1; fake(X1, digits(X) + blength, xlength - blength);
		BignumData Y1; fake(Y1, digits(Y) + blength, ylength - blength);

		BignumData Z0; init(Z0); mul(X0, Y0, Z0); // Z0 <- X0 * Y0
		BignumData Z2; init(Z2); mul(X1, Y1, Z2); // Z2 <- X1 * Y1

		BignumData TX; init(TX); add_u(X1, X0, TX); // TX <- X1 + X0
		BignumData TY; init(TY); add_u(Y1, Y0, TY); // TY <- Y1 + Y0

		BignumData & Z1 = TX; mul(TX, TY, Z1); sub(Z1, Z0, Z1); sub(Z1, Z2, Z1); // Z1 <- (TX * TY) - Z0 - Z2

		// Z <- (Z2 * B + Z1) * B + Z0
		BR_ASSERT(sign(Z0) == Sign::ZPOS);
		BR_ASSERT(sign(Z1) == Sign::ZPOS);
		BR_ASSERT(sign(Z2) == Sign::ZPOS);

		BignumData & T = Z2;
		reserve(Z, xlength + ylength);
		lsh_d(T, blength, T); add_u(T, Z1, T);
		lsh_d(T, blength, T); add_u(T, Z0, Z);
		clamp(Z);

		clear(Z0); clear(Z2);
		clear(TX); clear(TY);
	};
	static const auto toom3 = [](BignumData const & X, BignumData const & Y, BignumData & Z) {
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
		auto const xlength = length(X);
		auto const ylength = length(Y);
		auto const blength = (xlength < ylength ? xlength : ylength) / 3;

		// {Step1} Splitting
		BignumData X0; fake(X0, digits(X), blength); clamp(X0);
		BignumData Y0; fake(Y0, digits(Y), blength); clamp(Y0);

		BignumData X1; fake(X1, digits(X) + blength, blength); clamp(X1);
		BignumData Y1; fake(Y1, digits(Y) + blength, blength); clamp(Y1);

		BignumData X2; fake(X2, digits(X) + blength + blength, xlength - blength - blength);
		BignumData Y2; fake(Y2, digits(Y) + blength + blength, ylength - blength - blength);

		// {Step2} Evaluation
		BignumData TX1; init(TX1); BignumData TX2; init(TX2); BignumData TX3; init(TX3);
		BignumData TY1; init(TY1); BignumData TY2; init(TY2); BignumData TY3; init(TY3);

		add_u(X2, X0, TX1); // TX1 <- X2 + X0
		add_u(Y2, Y0, TY1); // TY1 <- Y2 + Y0

		sub(TX1, X1, TX2); // TX2 <- TX1 - X1 = X(-1)
		sub(TY1, Y1, TY2); // TY2 <- TY1 - Y1 = Y(-1)

		add_u(TX1, X1, TX1); // TX1 <- TX1 + X1 = X(1)
		add_u(TY1, Y1, TY1); // TY1 <- TY1 + Y1 = Y(1)

		add(TX2, X2, TX3); mul2(TX3, TX3); sub(TX3, X0, TX3); // TX3 <- (Tx2 + X2) * 2 - X0 = X(-2)
		add(TY2, Y2, TY3); mul2(TY3, TY3); sub(TY3, Y0, TY3); // TY3 <- (TY2 + Y2) * 2 - X0 = Y(-2)

		// {Step3} Pointwise multiplication
		BignumData W0; init(W0); mul( X0,  Y0, W0);                         // W0 <-  X0 *  Y0 = Z(0)   = [ 1  0  0  0  0]
		BignumData W1; init(W1); mul(TX1, TY1, W1); clear(TX1); clear(TY1); // W1 <- TX1 * TY1 = Z(1)   = [ 1  1  1  1  1]
		BignumData W2; init(W2); mul(TX2, TY2, W2); clear(TX2); clear(TY2); // W2 <- TX2 * TY2 = Z(-1)  = [ 1 -1  1 -1  1]
		BignumData W3; init(W3); mul(TX3, TY3, W3); clear(TX3); clear(TY3); // W3 <- TX3 * TY3 = Z(-2)  = [ 1 -2  4 -8 16]
		BignumData W4; init(W4); mul( X2,  Y2, W4);                         // W4 <-  X2 *  Y2 = Z(inf) = [ 0  0  0  0  1]

		// {Step4} Interpolation
		BignumData & Z0 = W0; // Z0 <- W0 = [ 1  0  0  0  0]
		BignumData & Z1 = W1;
		BignumData & Z2 = W2;
		BignumData & Z3 = W3;
		BignumData & Z4 = W4; // Z4 <- W4 = [ 0  0  0  0  1]

		sub(W3, W1, Z3); div_ud(Z3, 3, Z3); // Z3 <- (W3 - W1) / 3 = [ 0 -1  1 -3  5]

		sub(W1, W2, Z1); div2(Z1, Z1); // Z1 <- (W1 - W2) / 2 = [ 0  1  0  1  0]

		sub(W2, W0, Z2); // Z2 <- (W2 - W0) = [ 0 -1  1 -1  1]

		sub(Z2, Z3, Z3); div2(Z3, Z3); add(Z3, Z4, Z3); add(Z3, Z4, Z3); // Z3 <- (Z2 - Z3) / 2 + Z4 + Z4 = [ 0  0  0  1  0]

		add(Z2, Z1, Z2); sub(Z2, Z4, Z2); // Z2 <- Z2 + Z1 - Z4 = [ 0  0  1  0  0]

		sub(Z1, Z3, Z1); // Z1 <- Z1 - Z3 = [ 0  1  0  0  0]

		// {Step5} Recomposition
		// Z <- (((Z4 * B + Z3) * B + Z2) * B + Z1) * B + Z0
		BR_ASSERT(sign(Z0) == Sign::ZPOS);
		BR_ASSERT(sign(Z1) == Sign::ZPOS);
		BR_ASSERT(sign(Z2) == Sign::ZPOS);
		BR_ASSERT(sign(Z3) == Sign::ZPOS);
		BR_ASSERT(sign(Z4) == Sign::ZPOS);

		BignumData & T = Z4;
		reserve(Z, xlength + ylength);
		lsh_d(T, blength, T); add_u(T, Z3, T);
		lsh_d(T, blength, T); add_u(T, Z2, T);
		lsh_d(T, blength, T); add_u(T, Z1, T);
		lsh_d(T, blength, T); add_u(T, Z0, Z);
		clamp(Z);

		// {Clear}
		clear(W0); clear(W1); clear(W2); clear(W3); clear(W4);
	};
	auto const xlength = length(X);
	auto const ylength = length(Y);
	auto const min_length = xlength < ylength ? xlength : ylength;
	auto const zsign = sign(X) * sign(Z);
	if (min_length >= MUL_DOOR_TOOM) {
		toom3(X, Y, Z);
	} else if (min_length >= MUL_DOOR_KARATSUBA) {
		karatsuba(X, Y, Z);
	} else {
		base(X, Y, Z);
	}
	sign(Z) = zsign;
}

void BignumAlgorithm::mul_d(BignumData const & X, Digit d, BignumData & Z) {
	auto const xlength = length(X);
	auto const zlength = xlength + 1;

	reserve(Z, zlength);

	auto xds = digits(X);
	auto zds = digits(Z);

	UDDigit t = 0;
	for (auto xi = xlength; xi-- > 0;) {
		t += UDDigit(*xds++) * d;
		*zds++ = mod_radix(t);
		t = div_radix(t);
	}
	*zds++ = mod_radix(t);

	BR_ASSERT((xds - digits(X)) - xlength == 0);
	BR_ASSERT((zds - digits(Z)) - zlength == 0);

	length(Z) = zlength;
	clamp(Z);
}

void BignumAlgorithm::div_mod(BignumData const & X, BignumData const & Y, BignumData * Q, BignumData * R) {
	if (is_zero(Y)) {
		throw;
	}
	if (cmp_u(X, Y) == Relation::LT) {
		if (Q != nullptr) {
			set_zero(*Q);
		}
		if (R != nullptr) {
			copy(*R, X);
		}
		return;
	}

	auto const qsign = sign(X) * sign(Y);

	BignumData TQ; init(TQ);

	auto const tqlength = length(X) - length(Y) + 1;
	reserve(TQ, tqlength);

	auto tqds = digits(TQ) + tqlength;

	BignumData TX; init(TX); copy(TX, X); sign(TX) = Sign::ZPOS;
	BignumData TY; init(TY); copy(TY, Y); sign(TY) = Sign::ZPOS;

	auto const norm = count_leading_zeros(digits(TY)[length(TY)-1]);

	lsh_b(TX, norm, TX);
	lsh_b(TY, norm, TY);

	auto const lx = length(TX) - 1, ly = length(TY) - 1;
	lsh_d(TY, lx - ly, TY);
	*--tqds = 0;
	for (; cmp(TX, TY) != Relation::LT;) {
		++*tqds;
		sub(TX, TY, TX);
	}
	rsh_d(TY, lx - ly, TY);

	BignumData T1; init(T1); reserve(T1, 3);
	BignumData T2; init(T2); reserve(T2, 2);

	for (auto i = lx; i > ly; --i) {
		auto const j = i - ly - 1;
		if (i > length(TX)) {
			*--tqds = 0;
		} else {
			DDigit tqd;
			if (digits(TX)[i] == digits(TY)[ly]) {
				tqd = RADIX - 1;
			} else {
				auto t = ((UDDigit(digits(TX)[i]) << BIT_PER_DIGIT) | digits(TX)[i-1]) / digits(TY)[ly];
				tqd = t >= RADIX ? RADIX - 1 : t;
			}
			++tqd;

			do {
				--tqd;
				digits(T1)[0] = i > 1 ? digits(TX)[i - 2] : 0;
				digits(T1)[1] = i > 0 ? digits(TX)[i - 1] : 0;
				digits(T1)[2] = digits(TX)[i];
				length(T1) = 3;

				digits(T2)[0] = ly > 0 ? digits(TY)[ly - 1] : 0;
				digits(T2)[1] = digits(TY)[ly];
				length(T2) = 2;
				mul_d(T2, Digit(tqd), T2);
			} while (cmp_u(T1, T2) == Relation::LT);

			mul_d(TY, Digit(tqd), T1);
			lsh_d(T1, j, T1);
			sub(TX, T1, TX);

			if (TX.sign == Sign::NEG) {
				lsh_d(TY, j, T1);
				add(TX, T1, TX);
				--tqd;
			}

			*--tqds = Digit(tqd);
		}
	}

	length(TQ) = tqlength;

	if (Q != nullptr) {
		clamp(TQ);
		swap(*Q, TQ);
		sign(*Q) = qsign;
	}

	if (R != nullptr) {
		sign(TX) = is_zero(TX) ? Sign::ZPOS : sign(X);
		rsh_b(TX, norm, TX);
		swap(*R, TX);
	}

	clear(TQ);
	clear(TX); clear(TY);
	clear(T1); clear(T2);
}

auto BignumAlgorithm::div_mod_d(BignumData const & X, Digit d, BignumData & Z) -> Digit {
	if (d == 0) {
		throw;
	}

	auto const xlength = length(X);
	auto const zlength = xlength;

	reserve(Z, zlength);

	auto xds = digits(X) + xlength;
	auto zds = digits(Z) + zlength;

	UDDigit t = 0;
	Digit w;
	for (auto xi = xlength; xi-- > 0;) {
		t = (t << BIT_PER_DIGIT) | *--xds;
		if (t < d) {
			w = 0;
		} else {
			w = Digit(t / d);
			t %= d;
		}
		*--zds = w;
	}

	length(Z) = zlength;
	clamp(Z);

	return Digit(t);
}

auto BignumAlgorithm::mod_d(BignumData const & X, UDigit d) -> Digit {
	auto const xlength = length(X);

	auto xds = digits(X) + xlength;

	UDDigit t = 0;
	for (auto xi = xlength; xi-- > 0;) {
		t = (t << BIT_PER_DIGIT) | *--xds;
		if (t >= d) {
			t %= d;
		}
	}

	return Digit(t);
}

void BignumAlgorithm::bor(BignumData const & X, BignumData const & Y, BignumData & Z) {
	static const auto base = [](BignumData const & X, BignumData const & Y, BignumData & Z) {
		auto const xlength = length(X);
		auto const ylength = length(Y);
		auto const zlength = xlength;

		BR_ASSERT(xlength >= ylength);

		reserve(Z, zlength);

		auto xds = digits(X);
		auto yds = digits(Y);
		auto zds = digits(Z);

		duff_device(          ylength, [&](){ *zds++ = *xds++ | *yds++; });
		duff_device(xlength - ylength, [&](){ *zds++ = *xds++         ; });

		BR_ASSERT((xds - digits(X)) - xlength == 0);
		BR_ASSERT((yds - digits(Y)) - ylength == 0);
		BR_ASSERT((zds - digits(Z)) - zlength == 0);

		length(Z) = zlength;
		clamp(Z);
	};
	if (length(X) < length(Y)) {
		base(Y, X, Z);
	} else {
		base(X, Y, Z);
	}
	sign(Z) = sign(X) | sign(Y);
}

void BignumAlgorithm::band(BignumData const & X, BignumData const & Y, BignumData & Z) {
	static const auto base = [](BignumData const & X, BignumData const & Y, BignumData & Z) {
		auto const xlength = length(X);
		auto const ylength = length(Y);
		auto const zlength = xlength;

		BR_ASSERT(xlength >= ylength);

		reserve(Z, zlength);

		auto xds = digits(X);
		auto yds = digits(Y);
		auto zds = digits(Z);

		duff_device(          ylength, [&](){ *zds++ = *xds++ & *yds++; });
		duff_device(xlength - ylength, [&](){ *zds++ = *xds++         ; });

		BR_ASSERT((xds - digits(X)) - xlength == 0);
		BR_ASSERT((yds - digits(Y)) - ylength == 0);
		BR_ASSERT((zds - digits(Z)) - zlength == 0);

		length(Z) = zlength;
		clamp(Z);
	};
	if (length(X) < length(Y)) {
		base(Y, X, Z);
	} else {
		base(X, Y, Z);
	}
	sign(Z) = sign(X) & sign(Y);
}

void BignumAlgorithm::bxor(BignumData const & X, BignumData const & Y, BignumData & Z) {
	static const auto base = [](BignumData const & X, BignumData const & Y, BignumData & Z) {
		auto const xlength = length(X);
		auto const ylength = length(Y);
		auto const zlength = xlength;

		BR_ASSERT(xlength >= ylength);

		reserve(Z, zlength);

		auto xds = digits(X);
		auto yds = digits(Y);
		auto zds = digits(Z);

		duff_device(          ylength, [&](){ *zds++ = *xds++ ^ *yds++; });
		duff_device(xlength - ylength, [&](){ *zds++ = *xds++         ; });

		BR_ASSERT((xds - digits(X)) - xlength == 0);
		BR_ASSERT((yds - digits(Y)) - ylength == 0);
		BR_ASSERT((zds - digits(Z)) - zlength == 0);

		length(Z) = zlength;
		clamp(Z);
	};
	if (length(X) < length(Y)) {
		base(Y, X, Z);
	} else {
		base(X, Y, Z);
	}
	sign(Z) = sign(X) ^ sign(Y);
}

void BignumAlgorithm::sqr(BignumData const & X, BignumData & Z) {
	static const auto base = [](BignumData const & X, BignumData & Z) {
		auto const xlength = length(X);
		auto const tlength = xlength + xlength + 1;

		BignumData T; init(T); reserve(T, tlength); fill_digits_0(digits(T), tlength);

		for (auto xi = 0U; xi < xlength; ++xi) {
			auto const xdi = UDDigit(digits(X)[xi]);
			auto const xdh = div_radix(xdi * 2);
			auto const xdl = mod_radix(xdi * 2);

			UDDigit t = digits(T)[xi + xi] + xdi * xdi;
			digits(T)[xi + xi] = mod_radix(t);
			t = div_radix(t);

			for (auto xj = xi + 1; xj < xlength; ++xj) {
				auto const xdj = UDDigit(digits(X)[xj]);
				t += digits(T)[xi + xj] + xdl * xdj;
				digits(T)[xi + xj] = mod_radix(t);
				t = div_radix(t) + xdh * xdj;
			}

			t += digits(T)[xi + xlength];
			digits(T)[xi + xlength] = mod_radix(t);
			digits(T)[xi + xlength + 1] += mod_radix(div_radix(t));
		}

		length(T) = tlength;
		clamp(T);
		swap(T, Z);
		clear(T);
	};
	static const auto karatsuba = [](BignumData const & X, BignumData & Z) {
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
		auto const xlength = length(X);
		auto const blength = xlength / 2;

		BignumData X0; fake(X0, digits(X), blength); clamp(X0);

		BignumData X1; fake(X1, digits(X) + blength, xlength - blength);

		BignumData Z0; init(Z0); sqr(X0, Z0); // Z0 <- X0^2
		BignumData Z2; init(Z2); sqr(X1, Z2); // Z2 <- X1^2

		BignumData TX; init(TX); add_u(X1, X0, TX); // TX <- X1 + X0

		BignumData & Z1 = TX; sqr(TX, Z1); sub(Z1, Z0, Z1); sub(Z1, Z2, Z1); // Z1 <- TX^2 - Z0 - Z2

		// Z <- (Z2 * B + Z1) * B + Z0
		BR_ASSERT(sign(Z0) == Sign::ZPOS);
		BR_ASSERT(sign(Z1) == Sign::ZPOS);
		BR_ASSERT(sign(Z2) == Sign::ZPOS);

		BignumData & T = Z2;
		reserve(Z, xlength + xlength);
		lsh_d(T, blength, T); add_u(T, Z1, T);
		lsh_d(T, blength, T); add_u(T, Z0, Z);
		clamp(Z);

		clear(Z0); clear(Z2); clear(TX);
	};
	static const auto toom3 = [](BignumData const & X, BignumData & Z) {
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
		auto const xlength = length(X);
		auto const blength = xlength / 3;

		// {Step1} Splitting
		BignumData X0; fake(X0, digits(X), blength); clamp(X0);

		BignumData X1; fake(X1, digits(X) + blength, blength); clamp(X1);

		BignumData X2; fake(X2, digits(X) + blength + blength, xlength - blength - blength);

		// {Step2} Evaluation
		BignumData TX1; init(TX1);
		BignumData TX2; init(TX2);
		BignumData TX3; init(TX3);

		add_u(X2, X0, TX1); // TX1 <- X2 + X0

		sub(TX1, X1, TX2); // TX2 <- TX1 - X1 = X(-1)

		add_u(TX1, X1, TX1); // TX1 <- TX1 + X1 = X(1)

		add(TX2, X2, TX3); mul2(TX3, TX3); sub(TX3, X0, TX3); // TX3 <- (Tx2 + X2) * 2 - X0 = X(-2)

		// {Step3} Pointwise multiplication
		BignumData W0; init(W0); sqr( X0, W0); // W0 <-  X0^2 = Z(0)   = [ 1  0  0  0  0]
		BignumData W1; init(W1); sqr(TX1, W1); // W1 <- TX1^2 = Z(1)   = [ 1  1  1  1  1]
		BignumData W2; init(W2); sqr(TX2, W2); // W2 <- TX2^2 = Z(-1)  = [ 1 -1  1 -1  1]
		BignumData W3; init(W3); sqr(TX3, W3); // W3 <- TX3^2 = Z(-2)  = [ 1 -2  4 -8 16]
		BignumData W4; init(W4); sqr( X2, W4); // W4 <-  X2^2 = Z(inf) = [ 0  0  0  0  1]

		// {Step4} Interpolation
		BignumData & Z0 = W0; // Z0 <- W0 = [ 1  0  0  0  0]
		BignumData & Z1 = W1;
		BignumData & Z2 = W2;
		BignumData & Z3 = W3;
		BignumData & Z4 = W4; // Z4 <- W4 = [ 0  0  0  0  1]

		sub(W3, W1, Z3); div_ud(Z3, 3, Z3); // Z3 <- (W3 - W1) / 3 = [ 0 -1  1 -3  5]

		sub(W1, W2, Z1); div2(Z1, Z1); // Z1 <- (W1 - W2) / 2 = [ 0  1  0  1  0]

		sub(W2, W0, Z2); // Z2 <- (W2 - W0) = [ 0 -1  1 -1  1]

		sub(Z2, Z3, Z3); div2(Z3, Z3); add(Z3, Z4, Z3); add(Z3, Z4, Z3); // Z3 <- (Z2 - Z3) / 2 + Z4 + Z4 = [ 0  0  0  1  0]

		add(Z2, Z1, Z2); sub(Z2, Z4, Z2); // Z2 <- Z2 + Z1 - Z4 = [ 0  0  1  0  0]

		sub(Z1, Z3, Z1); // Z1 <- Z1 - Z3 = [ 0  1  0  0  0]

		// {Step5} Recomposition
		// Z <- (((Z4 * B + Z3) * B + Z2) * B + Z1) * B + Z0
		BR_ASSERT(sign(Z0) == Sign::ZPOS);
		BR_ASSERT(sign(Z1) == Sign::ZPOS);
		BR_ASSERT(sign(Z2) == Sign::ZPOS);
		BR_ASSERT(sign(Z3) == Sign::ZPOS);
		BR_ASSERT(sign(Z4) == Sign::ZPOS);

		BignumData & T = Z4;
		reserve(Z, xlength + xlength);
		lsh_d(T, blength, T); add_u(T, Z3, T);
		lsh_d(T, blength, T); add_u(T, Z2, T);
		lsh_d(T, blength, T); add_u(T, Z1, T);
		lsh_d(T, blength, T); add_u(T, Z0, Z);
		clamp(Z);

		// {Clear}
		clear(TX1); clear(TX2); clear(TX3);

		clear(W0); clear(W1); clear(W2); clear(W3); clear(W4);
	};
	auto const xlength = length(X);
	auto const zsign = sign(X) * sign(X);
	if (xlength >= SQR_DOOR_TOOM) {
		toom3(X, Z);
	} else if (xlength >= SQR_DOOR_KARATSUBA) {
		karatsuba(X, Z);
	} else {
		base(X, Z);
	}
	sign(Z) = zsign;
}

void BignumAlgorithm::power(BignumData const & X, Digit n, BignumData & Z) {
	BignumData T; init(T);
	set_uint(T, 1U);
	auto x = BIT_PER_DIGIT - count_leading_zeros(n);
	for (n = reverse_bits(n) >> count_leading_zeros(n); x-- > 0; n >>= 1) {
		sqr(T, T);
		if ((n & 1) != 0) {
			mul(T, X, T);
		}
	}
	swap(T, Z);
	clear(T);
}

void BignumAlgorithm::mul2(BignumData const & X, BignumData & Z) {
	auto const xlength = length(X);
	auto const zlength = xlength + 1;

	reserve(Z, zlength);

	auto xds = digits(X);
	auto zds = digits(Z);

	UDDigit t = 0;
	for (auto xi = xlength; xi-- > 0; ) {
		t |= UDDigit(*xds++) << 1;
		*zds++ = mod_radix(t);
		t = div_radix(t);
	}
	*zds++ = mod_radix(t);

	BR_ASSERT((xds - digits(X)) - xlength == 0);
	BR_ASSERT((zds - digits(Z)) - zlength == 0);

	sign(Z)   = sign(X);
	length(Z) = zlength;
	clamp(Z);
}

void BignumAlgorithm::div2(BignumData const & X, BignumData & Z) {
	auto const xlength = length(X);
	auto const zlength = xlength;

	reserve(Z, zlength);

	auto xds = digits(X) + xlength;
	auto zds = digits(Z) + zlength;

	UDDigit t = 0;
	for (auto xi = xlength; xi-- > 0; ) {
		t |= UDDigit(*--xds) << (BIT_PER_DIGIT - 1);
		*--zds = Digit(div_radix(t));
		t = mul_radix(t);
	}

	BR_ASSERT(xds == digits(X));
	BR_ASSERT(zds == digits(Z));

	sign(Z)   = sign(X);
	length(Z) = zlength;
	clamp(Z);
}

void BignumAlgorithm::lsh_b(BignumData const & X, Digit bn, BignumData & Z) {
	BR_ASSERT(0 <= bn && bn < BIT_PER_DIGIT);

	auto const xlength = length(X);
	auto const zlength = xlength + 1;

	reserve(Z, zlength);

	auto xds = digits(X);
	auto zds = digits(Z);

	UDDigit t = 0;
	for (auto xi = xlength; xi-- > 0; ) {
		t |= UDDigit(*xds++) << bn;
		*zds++ = mod_radix(t);
		t = div_radix(t);
	}
	*zds++ = mod_radix(t);

	BR_ASSERT((xds - digits(X)) - xlength == 0);
	BR_ASSERT((zds - digits(Z)) - zlength == 0);

	sign(Z)   = sign(X);
	length(Z) = zlength;
	clamp(Z);
}

void BignumAlgorithm::rsh_b(BignumData const & X, Digit bn, BignumData & Z) {
	BR_ASSERT(0 <= bn && bn < BIT_PER_DIGIT);

	auto const xlength = length(X);
	auto const zlength = xlength;

	reserve(Z, zlength);

	auto xds = digits(X) + xlength;
	auto zds = digits(Z) + zlength;

	UDDigit t = 0;
	bn = BIT_PER_DIGIT - bn;
	for (auto xi = xlength; xi-- > 0; ) {
		t |= UDDigit(*--xds) << bn;
		*--zds = Digit(div_radix(t));
		t = mul_radix(t);
	}

	BR_ASSERT(xds == digits(X));
	BR_ASSERT(zds == digits(Z));

	sign(Z)   = sign(X);
	length(Z) = zlength;
	clamp(Z);
}

void BignumAlgorithm::lsh_d(BignumData const & X, Digit dn, BignumData & Z) {
	BR_ASSERT(0 <= dn);

	auto const xlength = length(X);
	auto const zlength = xlength + dn;

	reserve(Z, zlength);

	auto xds = digits(X) + xlength;
	auto zds = digits(Z) + zlength;

	duff_device(xlength, [&](){ *--zds = *--xds; });
	duff_device(dn, [&](){ *--zds = 0; });

	BR_ASSERT(xds == digits(X));
	BR_ASSERT(zds == digits(Z));

	sign(Z)   = sign(X);
	length(Z) = zlength;
}

void BignumAlgorithm::rsh_d(BignumData const & X, Digit dn, BignumData & Z) {
	BR_ASSERT(0 <= dn);

	if (length(X) <= dn) {
		set_zero(Z);
		return;
	}

	auto const xlength = length(X);
	auto const zlength = xlength - dn;

	reserve(Z, zlength);

	auto xds = digits(X) + dn;
	auto zds = digits(Z);

	duff_device(zlength, [&](){ *zds++ = *xds++; });

	BR_ASSERT((xds - digits(X)) - xlength == 0);
	BR_ASSERT((zds - digits(Z)) - zlength == 0);

	sign(Z)   = sign(X);
	length(Z) = zlength;
}

void BignumAlgorithm::lsh(BignumData const & X, Digit n, BignumData & Z) {
	static const auto base = [](BignumData const & X, Digit n, BignumData & Z) {
		BR_ASSERT(0 <= n);

		auto const bn = n % BIT_PER_DIGIT;
		auto const dn = n / BIT_PER_DIGIT;

		auto const xlength = length(X);
		auto const zlength = xlength + dn + 1;

		reserve(Z, zlength);

		auto xds = digits(X) + xlength;
		auto zds = digits(Z) + zlength;

		UDDigit t = 0;
		for (auto xi = xlength; xi-- > 0; ) {
			t |= UDDigit(*--xds) << bn;
			*--zds = Digit(div_radix(t));
			t = mul_radix(t);
		}
		*--zds = Digit(div_radix(t));

		duff_device(dn, [&](){ *--zds = 0; });

		BR_ASSERT(xds == digits(X));
		BR_ASSERT(zds == digits(Z));

		sign(Z)   = sign(X);
		length(Z) = zlength;
		clamp(Z);
	};
	if (n < BIT_PER_DIGIT) {
		lsh_b(X, n, Z);
	} else if (n % BIT_PER_DIGIT == 0) {
		lsh_d(X, Digit(n / BIT_PER_DIGIT), Z);
	} else {
		base(X, n, Z);
	}
}

void BignumAlgorithm::rsh(BignumData const & X, Digit n, BignumData & Z) {
	static const auto base = [](BignumData const & X, Digit n, BignumData & Z) {
		BR_ASSERT(0 <= n);

		auto const bn = n % BIT_PER_DIGIT;
		auto const dn = n / BIT_PER_DIGIT;

		if (dn >= X.length) {
			set_zero(Z);
			return;
		}

		auto const xlength = length(X);
		auto const zlength = xlength - dn;

		reserve(Z, zlength);

		auto xds = digits(X) + dn;
		auto zds = digits(Z);

		UDDigit t = (*xds++) >> bn;
		for (auto zi = zlength; zi-- > 1;) {
			t |= UDDigit(*xds++) << (BIT_PER_DIGIT - bn);
			*zds++ = mod_radix(t);
			t = div_radix(t);
		}
		*zds++ = mod_radix(t);

		sign(Z)   = sign(X);
		length(Z) = zlength;
		clamp(Z);
	};
	if (n < BIT_PER_DIGIT) {
		rsh_b(X, n, Z);
	} else if (n % BIT_PER_DIGIT == 0) {
		rsh_d(X, Digit(n / BIT_PER_DIGIT), Z);
	} else {
		base(X, n, Z);
	}
}

String<> BignumAlgorithm::inspect(BignumData const & X) {
	String<> oss;

	oss << sign_to_nchar(X.sign) << "0x";

	for (Size i = X.length; i-- > 0;) {
		oss << X.digits[i];
		// oss << std::setfill('0') << std::setw(BIT_PER_DIGIT / 4) << std::hex << X.digits[i];
	}

	// return oss.str();
	return oss;
}

String<> BignumAlgorithm::to_s(BignumData const & X, Digit b, bool show_plus) {
	constexpr static auto ALPHABET = "0123456789abcdefghijklmnopqrstuvwxyz";
	static auto to_s_generic = [](BignumData const & X, Digit base) {
		String<> s;
		BignumData T; init(T); copy(T, X);
		do {
			s << ALPHABET[div_mod_d(T, base, T)];
		} while (!is_zero(T));
		clear(T);
		return String<>(s.rbegin(), s.rend());
	};
	static auto to_s_power_2 = [](BignumData const & X, Digit base) {
		auto const xlength = X.length;
		auto const bits_per_char = ilog2(base);
		auto mod_base_mask = (1 << bits_per_char) - 1;

		String<> s; s.reserve((X.length * BIT_PER_DIGIT - count_leading_zeros(X.digits[X.length - 1]) + bits_per_char) / bits_per_char);

		auto xds = X.digits + xlength;
		Digit buffer = *--xds;

		int bit_pos = BIT_PER_DIGIT - count_leading_zeros(buffer);
		if (auto t = bit_pos % bits_per_char) {
			bit_pos += bits_per_char - t;
		}

		for (auto xi = xlength - 1;;) {
			bit_pos -= bits_per_char;
			for (; bit_pos >= 0;) {
				s << ALPHABET[(buffer >> bit_pos) & mod_base_mask];
				bit_pos -= bits_per_char;
			}
			if (xi-- <= 0) {
				break;
			}
			auto temp = (buffer << -bit_pos) & mod_base_mask;
			buffer = *--xds;
			bit_pos += BIT_PER_DIGIT;
			s << ALPHABET[temp | (buffer >> bit_pos)];
		}

		return s;
	};

	if (b < 2 || 36 < b) {
		throw ArgumentException(__func__);
	}

	String<> s;
	if (X.sign == Sign::NEG) {
		s << '-';
	} else if (show_plus) {
		s << '+';
	}

	if (is_zero(X)) {
		return "0";
	} else {
		s << (is_power2(b) ? to_s_power_2(X, b) : to_s_generic(X, b));
		return s;
	}
}

Bignum const Bignum::ZERO;

} // namespace BR

