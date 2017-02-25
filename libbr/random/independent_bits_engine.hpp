/**
 * @file
 * @brief IndependentBitsEngine
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/ilog2.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/type_traits/integer_traits.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace Random {

/**
 *
 * @tparam TEngine
 * @tparam p
 * @tparam r
 */
template< typename TEngine, Size w, typename TUInt >
class IndependentBitsEngine;

} // inline namespace Random



inline namespace Random {

template< typename TEngine, Size w, typename TUInt >
class IndependentBitsEngine {
public:
	using Engine = TEngine;

	using Result = TUInt;

private:
	template< typename TUI, TUI R0, Size W, Size M >
	class GetN {
		constexpr static auto digits = IntegerTraits<TUI>::digits;
		constexpr static Size N = W / M + (W % M != 0);
		constexpr static Size W0 = W / N;
		constexpr static TUI Y0 = W0 < digits ? (R0 >> W0) << W0 : 0;
	public:
		constexpr static Size value = R0 - Y0 > Y0 / N ? N + 1 : N;
	};

	using EngineResult = typename Engine::Result;

	using WorkingResult = ConditionalByValue< sizeof(EngineResult) <= sizeof(Result), Result, EngineResult >;

	constexpr static WorkingResult r = Engine::max() - Engine::min() + WorkingResult(1);

	constexpr static auto digits = IntegerTraits<Result>::digits;
	constexpr static auto engine_digits = IntegerTraits<EngineResult>::digits;
	constexpr static auto working_digits = IntegerTraits<WorkingResult>::digits;
	constexpr static Size m = r == 0 ? working_digits : ilog2(r) + 1;
	constexpr static auto n = GetN< WorkingResult, r, w, m >::value;
	constexpr static Size w0 = w / n;
	constexpr static Size w1 = w0 + 1;
	constexpr static Size n0 = n - w % n;
	constexpr static WorkingResult y0 = w0 < working_digits ? (r >> w0) << w0 : 0;
	constexpr static WorkingResult y1 = w1 < working_digits ? (r >> w1) << w1 : 0;
	constexpr static EngineResult mask0 = ~EngineResult() >> (engine_digits - w0);
	constexpr static EngineResult mask1 = ~EngineResult() >> (engine_digits - w1);

	static_assert(0 < w && w <= digits,  "SubtractWithCarryEngine: invalid parameters");

public:
	constexpr static auto min() -> Result {
		return 0;
	}

	constexpr static auto max() -> Result {
		return w == digits ? ~Result() : (Result(1U) << w) - Result(1U);
	}

public:
	IndependentBitsEngine() {
	}

	explicit IndependentBitsEngine(Engine const & engine) : m_engine(engine) {
	}

	explicit IndependentBitsEngine(Engine && engine) : m_engine(move(engine)) {
	}

	explicit IndependentBitsEngine(Result seed) : m_engine(seed) {
	}

	auto base() const noexcept -> Engine {
		return m_engine;
	}

	auto seed() -> IndependentBitsEngine & {
		m_engine.seed();
		return *this;
	}

	auto seed(Result sd) -> IndependentBitsEngine & {
		m_engine.seed(sd);
		return *this;
	}

	auto operator()() -> Result {
		return m_eval(BooleanConstant< r != 0 >{});
	}

	auto discard(Size step) -> IndependentBitsEngine & {
		for (; step != 0; --step) {
			operator()();
		}
		return *this;
	}

	auto operator==(IndependentBitsEngine const & y) -> bool {
		return m_engine == y.m_engine;
	}

	auto operator!=(IndependentBitsEngine const & y) -> bool {
		return !(*this == y);
	}

private:
	auto m_eval(BooleanTrue) -> Result {
		Result s = 0;
		for (Size k = 0; k < n0; ++k) {
			EngineResult u;
			do {
				u = m_engine() - Engine::min();
			} while (u >= y0);
			s = (s << w0) + (u & mask0);
		}
		for (Size k = n0; k < n; ++k) {
			EngineResult u;
			do {
				u = m_engine() - Engine::min();
			} while (u >= y1);
			s = (s << w1) + (u & mask1);
		}
		return s;
	}

	auto m_eval(BooleanFalse) -> Result {
		return m_engine() & mask0;
	}

private:
	Engine m_engine;
}; // class IndependentBitsEngine< TEngine, w, TUInt >

} // inline namespace Random

} // namespace BR