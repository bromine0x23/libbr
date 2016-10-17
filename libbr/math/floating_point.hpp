#pragma once

#include <libbr/config.hpp>
#include <libbr/math/uint.hpp>
#include <libbr/type_operate/conditional.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/make_signed.hpp>

namespace BR {


namespace Detail {
namespace Math {

template< typename TUnderlying, Size exponent_bits, Size fraction_bits >
union FloatStorage {
	TUnderlying underlying;
	struct {
#if defined(BR_LITTLE_ENDIAN)
		TUnderlying fraction : 23;
		TUnderlying exponent : 8;
		TUnderlying sign : 1;
#else
		TUnderlying sign : 1;
		TUnderlying exponent : 8;
		TUnderlying fraction : 23;
#endif
	};
};

template< Size exponent_bits, Size fraction_bits >
struct FloatBasic {
	static_assert(exponent_bits == 0, "not implement");
	static_assert(exponent_bits != 0, "not implement");
	NullPointer storage;
};

template<>
struct FloatBasic< 8, 23 > {
	using Underlying = UInt32;
	FloatStorage< Underlying, 8, 23 > storage;
};

template<>
struct FloatBasic< 11, 52 > {
	using Underlying = UInt64;
	FloatStorage< UInt64, 11, 52 > storage;
};

template< Size exponent_bits, Size fraction_bits >
struct Float : FloatBasic< exponent_bits, fraction_bits > {
	using Base = FloatBasic< exponent_bits, fraction_bits >;

public:
	constexpr static auto SIGN_BITS = 1;
	constexpr static auto EXPONENT_BITS = exponent_bits;
	constexpr static auto FRACTION_BITS = fraction_bits;
	constexpr static auto BITS = SIGN_BITS + EXPONENT_BITS + FRACTION_BITS;

public:
	using Exponent = SelectScalarStorage< EXPONENT_BITS >;
	using Fraction = SelectScalarStorage< FRACTION_BITS >;
	using Significand = SelectScalarStorage< FRACTION_BITS + 1 >;

public:
	constexpr static auto RAW_EXPONENT_MAX = (1 << EXPONENT_BITS) - 1;
	constexpr static auto EXPONENT_BIAS = (1 << (EXPONENT_BITS - 1)) - 1;

public:

	Exponent exponent() const {
		return Base::storage.exponent - EXPONENT_BIAS;
	}

	Fraction fraction() const {
		return Base::storage.fraction;
	}

	Significand significand() const {
		return Base::storage.fraction | (1 << FRACTION_BITS);
	}

	bool is_normal() const {
		return 0 < Base::storage.exponent && Base::storage.exponent < RAW_EXPONENT_MAX;
	}

	bool is_finite() const {
		return Base::storage.exponent < RAW_EXPONENT_MAX;
	}

	bool is_inf() const {
		return Base::storage.exponent == RAW_EXPONENT_MAX && Base::storage.fraction == 0;
	}

	bool is_nan() const {
		return Base::storage.exponent == RAW_EXPONENT_MAX && Base::storage.fraction != 0;
	}

	typename Base::Underlying & underlying() {
		return Base::storage.underlying;
	}

	typename Base::Underlying underlying() const {
		return Base::storage.underlying;
	}

	Float operator+() const {
		Float Z;
		Z.storage = Base::storage;
		return Z;
	}

	Float operator-() const {
		Float Z;
		Z.storage.underlying = Base::storage.underlying;
		Z.storage.sign = Base::storage.sign ^ 1;
		return Z;
	}

private:

}; // class Float

} // namespace Math
} // namespace Detail

// using Float32 = Detail::Math::Float< 8, 23 >;
// using Float64 = Detail::Math::Float< 11, 52 >;

} // namespace BR