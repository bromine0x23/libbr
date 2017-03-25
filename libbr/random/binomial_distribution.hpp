/**
 * @file
 * @brief
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/operators/equality_comparable.hpp>

namespace BR {

inline namespace Random {

template< typename TInt = SInt >
class BinomialDistribution {
public:
	using Result = TInt;

	struct Parameter : public EqualityComparable<Parameter> {
	public:
		using Distribution = BinomialDistribution;

	public:
		explicit Parameter(Result t = 1, DFloat p = 0.5) : m_t(t), m_p(p) {
			if (0 < m_p && m_p < 1) {
				m_r0 = Result((m_t + 1) * m_p);
				__pr_ = _VSTD::exp(_VSTD::lgamma(__t_ + 1.) - _VSTD::lgamma(__r0_ + 1.) -
				                   _VSTD::lgamma(__t_ - __r0_ + 1.) + __r0_ * _VSTD::log(__p_) +
				                   (__t_ - __r0_) * _VSTD::log(1 - __p_));
				__odds_ratio_ = __p_ / (1 - __p_);
			}
		}

		auto t() const -> Result {
			return m_t;
		}

		auto p() const -> DFloat {
			return m_p;
		}

		auto operator==(Parameter const & y) const -> bool {
			return m_t == y.m_t && m_p == y.m_p;
		}
	private:
		Result m_t;
		DFloat m_p;
		DFloat m_pr;
		DFloat __odds_ratio_;
		Result m_r0;
	}; // struct Parameter


	explicit BinomialDistribution(Result t = 1, DFloat p = 0.5) : m_parameter(Parameter(t, p)) {
	}

	explicit BinomialDistribution(Parameter const & parameter) : m_parameter(parameter) {
	}

	void reset() {
	}

	template< typename TGenerator >
	auto operator()(TGenerator & generator) -> Result {
		return operator()(generator, m_parameter);
	}

	template< typename TGenerator >
	auto operator()(TGenerator & generator, Parameter const & parameter) -> Result;

	auto t() const -> DFloat {
		return m_parameter.t();
	}

	auto p() const -> DFloat {
		return m_parameter.p();
	}

	auto parameter() const -> Parameter {
		return m_parameter;
	}

	auto min() const -> Result {
		return 0;
	}

	auto max() const -> Result {
		return t();
	}

	auto operator==(BinomialDistribution const & y) const -> Boolean {
		return m_parameter == y.m_parameter;
	}

private:
	Parameter m_parameter;

}; // class BinomialDistribution<TInt>

} // namespace Random

} // namespace BR
