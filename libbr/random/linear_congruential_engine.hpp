/**
 * @file
 * @brief LinearCongruentialEngine
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace Random {

/**
 * x<sub>i+1</sub> ← (a x<sub>i</sub> + c) mod m
 *
 * @tparam TUInt integral type
 * @tparam a multiplier
 * @tparam c increment
 * @tparam m modulus
 */
template< typename TUInt, TUInt a, TUInt c, TUInt m >
class LinearCongruentialEngine;

using MinimalStandard1988 = LinearCongruentialEngine<UInt32, 16807, 0, 0x7FFFFFFFU>;

using MinimalStandard1993 = LinearCongruentialEngine<UInt32, 48271, 0, 0x7FFFFFFFU>;

} // namespace Random



namespace Detail {
namespace Random {

template< typename TUInt, TUInt a, TUInt c, TUInt m, bool might_overflow = (a != 0 && m != 0 && m - 1 > (TUInt(~0) - c) / a) >
struct LinearCongruentialEngineNext;

#if defined(BR_HAS_INT128)
template< UInt128 a, UInt128 c, UInt128 m >
struct LinearCongruentialEngineNext<UInt128, a, c, m, true> {
	using Result = UInt64;
	static auto next(Result x) -> Result {
		constexpr auto q = m / a;
		constexpr auto r = m % a;
		auto t0 = a * (x % q);
		auto t1 = r * (x / q);
		x = t0 + (t0 < t1) * m - t1;
		x += c - (x >= m - c) * m;
		return x;
	}
};

template< UInt128 a, UInt128 m >
struct LinearCongruentialEngineNext<UInt128, a, 0, m, true> {
	using Result = UInt128;
	static auto next(Result x) -> Result {
		constexpr Result q = m / a;
		constexpr Result r = m % a;
		Result t0 = a * (x % q);
		Result t1 = r * (x / q);
		x = t0 + (t0 < t1) * m - t1;
		return x;
	}
};

template< UInt128 a, UInt128 c, UInt128 m >
struct LinearCongruentialEngineNext<UInt128, a, c, m, false> {
	using Result = UInt128;
	static auto next(Result x) -> Result {
		return (a * x + c) % m;
	}
};

template< UInt128 a, UInt128 c >
struct LinearCongruentialEngineNext<UInt128, a, c, 0, false> {
	using Result = UInt128;
	static auto next(Result x) -> Result {
		return a * x + c;
	}
};
#endif

template< UInt64 a, UInt64 c, UInt64 m >
struct LinearCongruentialEngineNext<UInt64, a, c, m, true> {
	using Result = UInt64;
	static auto next(Result x) -> Result {
		constexpr auto q = m / a;
		constexpr auto r = m % a;
		auto t0 = a * (x % q);
		auto t1 = r * (x / q);
		x = t0 + (t0 < t1) * m - t1;
		x += c - (x >= m - c) * m;
		return x;
	}
};

template< UInt64 a, UInt64 m >
struct LinearCongruentialEngineNext<UInt64, a, 0, m, true> {
	using Result = UInt64;
	static auto next(Result x) -> Result {
		constexpr Result q = m / a;
		constexpr Result r = m % a;
		Result t0 = a * (x % q);
		Result t1 = r * (x / q);
		x = t0 + (t0 < t1) * m - t1;
		return x;
	}
};

template< UInt64 a, UInt64 c, UInt64 m >
struct LinearCongruentialEngineNext<UInt64, a, c, m, false> {
	using Result = UInt64;
	static auto next(Result x) -> Result {
		return (a * x + c) % m;
	}
};

template< UInt64 a, UInt64 c >
struct LinearCongruentialEngineNext<UInt64, a, c, 0, false> {
	using Result = UInt64;
	static auto next(Result x) -> Result {
		return a * x + c;
	}
};

template< UInt32 a, UInt32 c, UInt32 m >
struct LinearCongruentialEngineNext<UInt32, a, c, m, true> {
	using Result = UInt32;
	static auto next(Result x) -> Result {
		constexpr auto q = m / a;
		constexpr auto r = m % a;
		auto t0 = a * (x % q);
		auto t1 = r * (x / q);
		x = t0 + (t0 < t1) * m - t1;
		x += c - (x >= m - c) * m;
		return x;
	}
};

template< UInt32 a, UInt32 m >
struct LinearCongruentialEngineNext<UInt32, a, 0, m, true> {
	using Result = UInt32;
	static auto next(Result x) -> Result {
		constexpr Result q = m / a;
		constexpr Result r = m % a;
		Result t0 = a * (x % q);
		Result t1 = r * (x / q);
		x = t0 + (t0 < t1) * m - t1;
		return x;
	}
};

template< UInt32 a, UInt32 c, UInt32 m >
struct LinearCongruentialEngineNext<UInt32, a, c, m, false> {
	using Result = UInt32;
	static auto next(Result x) -> Result {
		return (a * x + c) % m;
	}
};

template< UInt32 a, UInt32 c >
struct LinearCongruentialEngineNext<UInt32, a, c, 0, false> {
	using Result = UInt32;
	static auto next(Result x) -> Result {
		return a * x + c;
	}
};

template< UInt16 a, UInt16 c, UInt16 m, bool might_overflow >
struct LinearCongruentialEngineNext<UInt16, a, c, m, might_overflow> {
	using Result = UInt16;
	static auto next(Result x) -> Result {
		return Result(LinearCongruentialEngineNext<UInt32, a, c, m>::next(x));
	}
};

template< UInt8 a, UInt8 c, UInt8 m, bool might_overflow >
struct LinearCongruentialEngineNext<UInt8, a, c, m, might_overflow> {
	using Result = UInt8;
	static auto next(Result x) -> Result {
		return Result(LinearCongruentialEngineNext<UInt32, a, c, m>::next(x));
	}
};

} // namespace Random
} // namespace Detail

inline namespace Random {

template< typename TUInt, TUInt a, TUInt c, TUInt m >
class LinearCongruentialEngine {
public:
	using Result = TUInt;

public:
	constexpr static auto multiplier = a;
	constexpr static auto increment = c;
	constexpr static auto modulus = m;
	constexpr static auto default_seed = Result(1);

private:
	static_assert(modulus == 0 || multiplier < modulus, "LinearCongruentialEngine: invalid parameters");
	static_assert(modulus == 0 || increment  < modulus, "LinearCongruentialEngine: invalid parameters");

public:
	explicit LinearCongruentialEngine(Result s = default_seed) {
		seed(s);
	}

	constexpr static auto min() -> Result {
		return increment == 0U ? 1U: 0U;
	}

	constexpr static auto max() -> Result {
		return modulus - 1U;
	}

	auto seed(Result s = default_seed) -> LinearCongruentialEngine & {
		m_seed(BooleanConstant<modulus == 0>{}, BooleanConstant<increment == 0>{}, s);
		return *this;
	}

	auto operator()() -> Result {
		return m_x = Detail::Random::LinearCongruentialEngineNext< Result, multiplier, increment, modulus >::next(m_x);
	}

	auto discard(Size step) -> LinearCongruentialEngine & {
		for (; step != 0; --step) {
			operator()();
		}
		return *this;
	}

	auto operator==(LinearCongruentialEngine const & y) -> bool {
		return m_x == y.m_x;
	}

	auto operator!=(LinearCongruentialEngine const & y) -> bool {
		return !(*this == y);
	}

private:
	void m_seed(BooleanTrue, BooleanTrue, Result s) {
		m_x = s == 0 ? 1 : s;
	}
	void m_seed(BooleanTrue, BooleanFalse, Result s) {
		m_x = s;
	}

	void m_seed(BooleanFalse, BooleanTrue, Result s) {
		m_x = s % modulus == 0 ? 1 : s % modulus;
	}

	void m_seed(BooleanFalse, BooleanFalse, Result s) {
		m_x = s % modulus;
	}

private:
	Result m_x;
}; // class LinearCongruentialEngine<TUInt, a, c, m>

} // inline namespace Random

} // namespace BR