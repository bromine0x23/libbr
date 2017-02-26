/**
 * @file
 * @brief ShuffleOrderEngine
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/equal.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/random/linear_congruential_engine.hpp>

namespace BR {

inline namespace Random {

/**
 *
 * @tparam TEngine
 * @tparam k
 */
template< typename TEngine, Size k >
class ShuffleOrderEngine;

} // inline namespace Random



inline namespace Random {

template< typename TEngine, Size k >
class ShuffleOrderEngine : public EqualityComparable< ShuffleOrderEngine< TEngine, k > > {
public:
	using Engine = TEngine;

	using Result = typename TEngine::Result;

public:
	static constexpr auto table_size = k;

private:
	static_assert(0 < table_size, "ShuffleOrderEngine: invalid parameters");


public:
	static constexpr auto min() -> Result {
		return Engine::min();
	}

	static constexpr auto max() -> Result {
		return Engine::max();
	}

public:
	ShuffleOrderEngine() {
		m_init();
	}

	explicit ShuffleOrderEngine(Engine const & engine) : m_engine(engine) {
		m_init();
	}

	explicit ShuffleOrderEngine(Engine && engine) : m_engine(move(engine)) {
		m_init();
	}

	explicit ShuffleOrderEngine(Result seed) : m_engine(seed) {
		m_init();
	}

	auto base() const noexcept -> Engine {
		return m_engine;
	}

	auto seed() -> ShuffleOrderEngine & {
		m_engine.seed();
		m_init();
		return *this;
	}

	auto seed(Result seed) -> ShuffleOrderEngine & {
		m_engine.seed(seed);
		m_init();
		return *this;
	}

	auto operator()() -> Result {
		constexpr auto factor = table_size / (max() - min() + 1.0);
		Size j = factor * (m_last - min());
		m_last = m_table[j];
		m_table[j] = m_engine();
		return m_last;
	}

	auto discard(Size step) -> ShuffleOrderEngine & {
		for (; step != 0; --step) {
			operator()();
		}
		return *this;
	}

	auto operator==(ShuffleOrderEngine const & y) -> bool {
		return m_last == y.m_last && equal(m_table, m_table + table_size, y.m_table) && m_engine == y.m_engine;
	}

private:
	void m_init() {
		for (Size i = 0; i < table_size; ++i) {
			m_table[i] = m_engine();
		}
		m_last = m_engine();
	}

private:
	Engine m_engine;
	Result m_table[table_size];
	Result m_last;
}; // class ShuffleOrderEngine< TUInt, k >

} // namespace Random

} // namespace BR