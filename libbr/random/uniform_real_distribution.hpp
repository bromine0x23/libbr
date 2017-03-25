/**
 * @file
 * @brief UniformRealDistribution
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/random/generate_canonical.hpp>
#include <libbr/type_traits/floating_point_traits.hpp>

namespace BR {

inline namespace Random {

template< typename TReal = DFloat >
class UniformRealDistribution : public EqualityComparable< UniformRealDistribution<TReal> > {
public:
	using Result = TReal;

	struct Parameter : public EqualityComparable<Parameter> {
	public:
		using Distribution = UniformRealDistribution;

	public:
		explicit Parameter(Result a = 0, Result b = 1) : m_a(a), m_b(b) {}

		constexpr auto a() const -> Result {
			return m_a;
		}

		constexpr auto b() const -> Result {
			return m_b;
		}

		constexpr auto operator==(Parameter const & y) const -> bool {
			return m_a == y.m_a && m_b == y.m_b;
		}

	private:
		Result m_a;
		Result m_b;
	}; // struct Parameter

public:
	constexpr explicit UniformRealDistribution(Result a = 0, Result b = 1) : m_parameter(Parameter(a, b)) {
	}

	constexpr explicit UniformRealDistribution(Parameter const & parameter) : m_parameter(parameter) {
	}

	void reset() {
	}

	template< typename TGenerator >
	auto operator()(TGenerator & generator) -> Result {
		return operator()(generator, m_parameter);
	}

	template< typename TGenerator >
	auto operator()(TGenerator & generator, Parameter const & parameter) -> Result {
		return (parameter.b() - parameter.a()) * generate_canonical<Result, FloatingPointTraits<Result>::digits >(generator) + parameter.a();
	}

	constexpr auto a() const -> Result {
		return m_parameter.a();
	}

	constexpr auto b() const -> Result {
		return m_parameter.b();
	}

	constexpr auto parameter() const -> Parameter {
		return m_parameter;
	}

	void parameter(Parameter const & parameter) {
		m_parameter = parameter;
	}

	constexpr auto min() const -> Result {
		return a();
	}

	constexpr auto max() const -> Result {
		return b();
	}

	constexpr auto operator==(UniformRealDistribution const & y) const -> Boolean {
		return m_parameter == y.m_parameter;
	}

private:
	Parameter m_parameter;
}; // class UniformRealDistribution<TReal>

} // namespace Random

} // namespace BR
