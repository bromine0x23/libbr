/**
 * @file
 * @brief IndependentBitsEngine
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/ilog2.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/type_traits/enable_if.hpp>
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
class IndependentBitsEngine : public EqualityComparable< IndependentBitsEngine< TEngine, w, TUInt > > {
public:
	using Engine = TEngine;

	using Result = TUInt;

private:
	template< typename TUI, TUI R0, Size W, Size M >
	class GetN {
		static constexpr auto digits = IntegerTraits<TUI>::digits;
		static constexpr Size N = W / M + (W % M != 0);
		static constexpr Size W0 = W / N;
		static constexpr TUI Y0 = W0 < digits ? (R0 >> W0) << W0 : 0;
	public:
		static constexpr Size value = R0 - Y0 > Y0 / N ? N + 1 : N;
	};

	using EngineResult = typename Engine::Result;

	using WorkingResult = ConditionalByValue< sizeof(EngineResult) <= sizeof(Result), Result, EngineResult >;

	static constexpr WorkingResult r = Engine::max() - Engine::min() + WorkingResult(1);

	static constexpr auto digits = IntegerTraits<Result>::digits;
	static constexpr auto engine_digits = IntegerTraits<EngineResult>::digits;
	static constexpr auto working_digits = IntegerTraits<WorkingResult>::digits;
	static constexpr Size m = r == 0 ? working_digits : ilog2(r) + 1;
	static constexpr auto n = GetN< WorkingResult, r, w, m >::value;
	static constexpr Size w0 = w / n;
	static constexpr Size n0 = n - w % n;
	static constexpr WorkingResult y0 = w0 < working_digits     ? (r >>  w0     ) <<  w0      : 0;
	static constexpr WorkingResult y1 = w0 < working_digits - 1 ? (r >> (w0 + 1)) << (w0 + 1) : 0;
	static constexpr EngineResult mask0 = w0 > 0                  ? EngineResult(~0) >> (engine_digits -  w0     ) : EngineResult( 0);
	static constexpr EngineResult mask1 = w0 < working_digits - 1 ? EngineResult(~0) >> (engine_digits - (w0 + 1)) : EngineResult(~0);

	static_assert(0 < w && w <= digits,  "IndependentBitsEngine: invalid parameters");

public:
	static constexpr auto min() -> Result {
		return 0;
	}

	static constexpr auto max() -> Result {
		return w == digits ? Result(~0) : (Result(1U) << w) - Result(1U);
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
	template< Size count >
	auto m_lsh(Result x) -> EnableIfByValue< (count < working_digits), Result > {
		return x << count;
	}

	template< Size count >
	auto m_lsh(Result x) -> EnableIfByValue< (count >= working_digits), Result > {
		return Result(0);
	}

	auto m_eval(BooleanTrue) -> Result {
		Result s = 0;
		for (Size k = 0; k < n0; ++k) {
			EngineResult u;
			do {
				u = m_engine() - Engine::min();
			} while (u >= y0);
			s = static_cast<Result>(m_lsh<w0>(s) + (u & mask0));
		}
		for (Size k = n0; k < n; ++k) {
			EngineResult u;
			do {
				u = m_engine() - Engine::min();
			} while (u >= y1);
			s = static_cast<Result>(m_lsh<w0 + 1>(s) + (u & mask1));
		}
		return s;
	}

	auto m_eval(BooleanFalse) -> Result {
		return m_engine() & mask0;
	}

private:
	Engine m_engine;
}; // class IndependentBitsEngine< TEngine, w, TUInt >

} // namespace Random

} // namespace BR