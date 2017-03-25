/**
 * @file
 * @brief BernoulliDistribution
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/random/uniform_real_distribution.hpp>

namespace BR {

inline namespace Random {

class BernoulliDistribution : public EqualityComparable<BernoulliDistribution> {
public:
	using Result = Boolean;

	struct Parameter : public EqualityComparable<Parameter> {
	public:
		using Distribution = BernoulliDistribution;

	public:
		constexpr explicit Parameter(DFloat p = 0.5) : m_p(p) {}

		constexpr auto p() const -> DFloat {
			return m_p;
		}

		constexpr auto operator==(Parameter const & y) const -> bool {
			return m_p == y.m_p;
		}
	private:
		DFloat m_p;
	}; // struct Parameter

public:
	constexpr explicit BernoulliDistribution(DFloat p = 0.5) : m_parameter(Parameter(p)) {
	}

	constexpr explicit BernoulliDistribution(Parameter const & parameter) : m_parameter(parameter) {
	}

	void reset() {
	}

	template< typename TGenerator >
	auto operator()(TGenerator & generator) -> Result {
		return operator()(generator, m_parameter);
	}

	template< typename TGenerator >
	auto operator()(TGenerator & generator, Parameter const & parameter) -> Result {
		UniformRealDistribution<DFloat> distribution;
		return distribution(generator) < parameter.p();
	}

	constexpr auto p() const -> DFloat {
		return m_parameter.p();
	}

	constexpr auto parameter() const -> Parameter {
		return m_parameter;
	}

	void parameter(Parameter const & parameter) {
		m_parameter = parameter;
	}

	constexpr auto min() const -> Result {
		return false;
	}

	constexpr auto max() const -> Result {
		return true;
	}

	constexpr auto operator==(BernoulliDistribution const & y) const -> Boolean {
		return m_parameter == y.m_parameter;
	}

private:
	Parameter m_parameter;

}; // class BernoulliDistribution

} // namespace Random

} // namespace BR
