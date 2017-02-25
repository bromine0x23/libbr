/**
 * @file
 * @brief DiscardBlockEngine
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/random/subtract_with_carry_engine.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Random {

/**
 *
 * @tparam TEngine
 * @tparam p
 * @tparam r
 */
template< typename TEngine, Size p, Size r >
class DiscardBlockEngine;

using Ranlux24 = DiscardBlockEngine< Ranlux24Base, 223, 23 >;

using Ranlux48 = DiscardBlockEngine< Ranlux48Base, 389, 11 >;

} // inline namespace Random



inline namespace Random {

template< typename TEngine, Size p, Size r >
class DiscardBlockEngine {
public:
	using Engine = TEngine;

	using Result = typename TEngine::Result;

public:
	constexpr static auto block_size = p;
	constexpr static auto used_size  = r;

private:
	static_assert(0 <  r && r <= p, "DiscardBlockEngine: invalid parameters");

public:
	constexpr static auto min() -> Result {
		return Engine::min();
	}

	constexpr static auto max() -> Result {
		return Engine::max();
	}

public:
	DiscardBlockEngine() : m_count(0) {
	}

	explicit DiscardBlockEngine(Engine const & engine) : m_engine(engine), m_count(0) {
	}

	explicit DiscardBlockEngine(Engine && engine) : m_engine(move(engine)), m_count(0) {
	}

	explicit DiscardBlockEngine(Result seed) : m_engine(seed), m_count(0) {
	}

	auto base() const noexcept -> Engine {
		return m_engine;
	}

	auto seed() -> DiscardBlockEngine & {
		m_engine.seed();
		m_count = 0;
		return *this;
	}

	auto seed(Result sd) -> DiscardBlockEngine & {
		m_engine.seed(sd);
		m_count = 0;
		return *this;
	}

	auto operator()() -> Result {
		if (m_count >= used_size) {
			m_engine.discard(block_size - used_size);
			m_count = 0;
		}
		++m_count;
		return m_engine();
	}

	auto discard(Size step) -> DiscardBlockEngine & {
		for (; step != 0; --step) {
			operator()();
		}
		return *this;
	}

	auto operator==(DiscardBlockEngine const & y) -> bool {
		return m_count == y.m_count && m_engine == y.m_engine;
	}

	auto operator!=(DiscardBlockEngine const & y) -> bool {
		return !(*this == y);
	}

private:
	Engine m_engine;
	SInt m_count;
}; // class DiscardBlockEngine< TUInt p, r >

} // inline namespace Random

} // namespace BR