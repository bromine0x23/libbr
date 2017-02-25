/**
 * @file
 * @brief MersenneTwisterEngine
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/type_traits/integer_traits.hpp>

namespace BR {

inline namespace Random {

/**
 * <a href="https://en.wikipedia.org/wiki/Mersenne_Twister">MersenneTwisterEngine</a>
 *
 * @tparam TUInt
 * @tparam w word size
 * @tparam n state size
 * @tparam m shift size
 * @tparam r mask bits
 * @tparam a xor mask
 * @tparam u tempering u
 * @tparam d tempering d
 * @tparam s tempering s
 * @tparam b tempering b
 * @tparam t tempering t
 * @tparam c tempering c
 * @tparam l tempering l
 * @tparam f initialization multiplier
 */
template< typename TUInt, Size w, Size n, Size m, Size r, TUInt a, Size u, TUInt d, Size s, TUInt b, Size t, TUInt c, Size l, TUInt f >
class MersenneTwisterEngine;

using MT19937 = MersenneTwisterEngine< UInt32, 32, 624, 397, 31, 0x9908B0DFU, 11, 0xFFFFFFFFU, 7, 0x9D2C5680U, 15, 0xEFC60000U, 18, 1812433253>;

using MT19937_64 = MersenneTwisterEngine< UInt64, 64, 312, 156, 31, 0xB5026F5AA96619E9ULL, 29, 0x5555555555555555ULL, 17, 0x71D67FFFEDA60000ULL, 37, 0xFFF7EEE000000000ULL, 43, 6364136223846793005ULL>;

} // inline namespace Random



inline namespace Random {

template< typename TUInt, Size w, Size n, Size m, Size r, TUInt a, Size u, TUInt d, Size s, TUInt b, Size t, TUInt c, Size l, TUInt f >
class MersenneTwisterEngine {
public:
	using Result = TUInt;

public:
	constexpr static auto word_size = w;
	constexpr static auto state_size = n;
	constexpr static auto shift_size = m;
	constexpr static auto mask_bits = r;
	constexpr static auto xor_mask = a;
	constexpr static auto tempering_u = u;
	constexpr static auto tempering_d = d;
	constexpr static auto tempering_s = s;
	constexpr static auto tempering_b = b;
	constexpr static auto tempering_t = t;
	constexpr static auto tempering_c = c;
	constexpr static auto tempering_l = l;
	constexpr static auto initialization_multiplier = f;
	constexpr static auto default_seed = Result(5489U);

private:
	constexpr static auto digits = IntegerTraits<Result>::digits;

	static_assert(2 <= w && w <= digits, "MersenneTwisterEngine: invalid parameters");
	static_assert(0 <  m && m <= n, "MersenneTwisterEngine: invalid parameters");
	static_assert(r <= w, "MersenneTwisterEngine: invalid parameters");
	static_assert(u <= w, "MersenneTwisterEngine: invalid parameters");
	static_assert(s <= w, "MersenneTwisterEngine: invalid parameters");
	static_assert(t <= w, "MersenneTwisterEngine: invalid parameters");
	static_assert(l <= w, "MersenneTwisterEngine: invalid parameters");

public:
	constexpr static auto min() -> Result {
		return 0U;
	}

	constexpr static auto max() -> Result {
		return word_size == digits ? ~Result() : (Result(1U) << word_size) - Result(1U);
	}

private:
	static_assert(min() < max(), "MersenneTwisterEngine: invalid parameters");
	static_assert(a <= max(), "MersenneTwisterEngine: invalid parameters");
	static_assert(b <= max(), "MersenneTwisterEngine: invalid parameters");
	static_assert(c <= max(), "MersenneTwisterEngine: invalid parameters");
	static_assert(d <= max(), "MersenneTwisterEngine: invalid parameters");
	static_assert(f <= max(), "MersenneTwisterEngine: invalid parameters");

public:
	explicit MersenneTwisterEngine(Result sd = default_seed) {
		seed(sd);
	}

	auto seed(Result sd = default_seed) -> MersenneTwisterEngine & {
		m_state[0] = sd & max();
		for (Size i = 1; i < state_size; ++i) {
			auto x = m_state[i - 1];
			x ^= x >> (word_size - 2);
			x *= initialization_multiplier;
			x += i;
			x &= max();
			m_state[i] = x;
		}
		m_index = state_size;
		return *this;
	}

	auto operator()() -> Result {
		if (m_index >= state_size) {
			m_twist();
		}
		Result z = m_state[m_index++];
		z ^= (z >> u) & d;
		z ^= (z << s) & b;
		z ^= (z << t) & c;
		z ^= (z >> l);
		return z;
	}

	auto discard(Size step) -> MersenneTwisterEngine & {
		for (; step > state_size - m_index; ) {
			step -= state_size - m_index;
			m_twist();
		}
		m_index += step;
		return *this;
	}

	auto operator==(MersenneTwisterEngine const & y) -> bool {
		return (m_index == y.m_index) && equal(m_state, m_state + state_size, y.m_state);
	}

	auto operator!=(MersenneTwisterEngine const & y) -> bool {
		return !(*this == y);
	}

private:

	void m_twist() {
		constexpr Result mask = ~Result() << mask_bits;
		for (Size k = 0; k < (state_size - shift_size); ++k) {
			Result y = (m_state[k] & mask) | (m_state[k + 1] & ~mask);
			m_state[k] = m_state[k + shift_size] ^ (y >> 1) ^ ((y & 0x1) ? xor_mask : 0);
		}
		for (Size k = state_size - shift_size; k < state_size - 1; ++k) {
			Result y = (m_state[k] & mask) | (m_state[k + 1] & ~mask);
			m_state[k] = m_state[k + shift_size - state_size] ^ (y >> 1) ^ ((y & 0x1) ? xor_mask : 0);
		}
		Result y = (m_state[state_size - 1] & mask) | (m_state[0] & ~mask);
		m_state[state_size - 1] = m_state[shift_size - 1] ^ (y >> 1) ^ ((y & 0x1) ? xor_mask : 0);
		m_index = 0;
	}

private:
	Result m_state[state_size];
	Size m_index;
}; // class MersenneTwisterEngine<TUInt w, n, m, r, a, u, d, s, b, t, c, l, f>

} // inline namespace Random

} // namespace BR