/**
 * @file
 * @brief SubtractWithCarryEngine
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/random/linear_congruential_engine.hpp>
#include <libbr/type_traits/integer_traits.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

inline namespace Random {

/**
 *
 * @tparam TUInt
 * @tparam w
 * @tparam s
 * @tparam r
 */
template< typename TUInt, Size w, Size s, Size r >
class SubtractWithCarryEngine;

} // inline namespace Random



inline namespace Random {

template< typename TUInt, Size w, Size s, Size r >
class SubtractWithCarryEngine : public EqualityComparable< SubtractWithCarryEngine< TUInt, w, s, r > > {
public:
	using Result = TUInt;

public:
	static constexpr auto word_size = w;
	static constexpr auto short_lag = s;
	static constexpr auto long_lag  = r;
	static constexpr auto default_seed = Result(19780503U);

private:
	static constexpr auto digits = IntegerTraits<Result>::digits;

	static_assert(0 < word_size && word_size <= digits,  "SubtractWithCarryEngine: invalid parameters");
	static_assert(0 < short_lag && short_lag < long_lag, "SubtractWithCarryEngine: invalid parameters");

public:
	static constexpr auto min() -> Result {
		return 0U;
	}

	static constexpr auto max() -> Result {
		return word_size == digits ? ~Result() : (Result(1U) << word_size) - Result(1U);
	}

private:
	static_assert(min() < max(), "SubtractWithCarryEngine: invalid parameters");

public:
	explicit SubtractWithCarryEngine(Result seed = default_seed) {
		this->seed(seed);
	}

	auto seed(Result seed = default_seed) -> SubtractWithCarryEngine & {
		m_seed(seed, IntegralConstant<UInt, 1 + (word_size - 1) / 32>{});
		return *this;
	}

	auto operator()() -> Result {
		auto const & term_s = m_terms[m_index < short_lag ? m_index + (long_lag - short_lag) : m_index - short_lag];
		auto & term_r = m_terms[m_index];
		auto new_carry = m_carry == 0 ? (term_s < term_r) : (term_s != 0) ? (term_s <= term_r) : 1;
		term_r = (term_s - term_r - m_carry) & max();
		m_carry = new_carry;
		if (++m_index >= long_lag) {
			m_index = 0;
		}
		return term_r;
	}

	auto discard(Size step) -> SubtractWithCarryEngine & {
		for (; step != 0; --step) {
			operator()();
		}
		return *this;
	}

	auto operator==(SubtractWithCarryEngine const & y) const -> bool {
		return (m_carry == y.m_carry) && (m_index == y.m_index) && equal(m_terms, m_terms + long_lag, y.m_terms);
	}

private:
	void m_seed(Result sd, IntegralConstant<UInt, 1>) {
		LinearCongruentialEngine<Result, 40014U, 0U, 2147483563U> engine(sd == 0U ? default_seed : sd);
		for (Size i = 0; i < long_lag; ++i) {
			m_terms[i] = static_cast<Result>(engine() & max());
		}
		m_carry = (m_terms[long_lag - 1] == 0);
		m_index = 0;
	}

	void m_seed(Result sd, IntegralConstant<UInt, 2>) {
		LinearCongruentialEngine<Result, 40014U, 0U, 2147483563U> engine(sd == 0U ? default_seed : sd);
		for (Size i = 0; i < long_lag; ++i) {
			auto t = engine();
			m_terms[i] = static_cast<Result>((t + (engine() << 32)) & max());
		}
		m_carry = (m_terms[long_lag - 1] == 0);
		m_index = 0;
	}

private:
	Result m_terms[long_lag];
	Result m_carry;
	Size   m_index;
}; // class SubtractWithCarryEngine< TUInt w, s, r >

} // namespace Random

} // namespace BR