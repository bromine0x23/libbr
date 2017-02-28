/**
 * @file
 * @brief ExponentialDistribution
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/log.hpp>
#include <libbr/random/generate_canonical.hpp>
#include <libbr/type_traits/floating_point_traits.hpp>
#include <libbr/operators/equality_comparable.hpp>

namespace BR {
inline namespace Random {

/**
 * @brief Produces real values on an <a href="http://en.wikipedia.com/wiki/Exponential_distribution">exponential distribution</a>
 * @tparam TReal The result type generated by the generator. The effect is undefined if this is not one of float, double, or long double.
 */
template< typename TReal = DFloat >
class ExponentialDistribution;



template< typename TReal >
class ExponentialDistribution : public EqualityComparable< ExponentialDistribution<TReal> > {
public:
	/**
	 * TReal
	 */
	using Result = TReal;

	/**
	 * The type of the parameter set.
	 */
	struct Parameter : public EqualityComparable<Parameter> {
	public:
		using Distribution = ExponentialDistribution;

	public:
		explicit Parameter(Result lambda = 1) : m_lambda(lambda) {}

		constexpr auto lambda() const -> Result {
			return m_lambda;
		}

		constexpr auto operator==(Parameter const & y) -> Boolean {
			return m_lambda == y.m_lambda;
		}

	private:
		Result m_lambda;
	}; // struct Parameter

public:
	/**
	 * @brief Constructs a new distribution object.
	 * @param lambda The λ distribution parameter (the rate parameter).
	 */
	constexpr explicit ExponentialDistribution(Result lambda = 1) : m_parameter(Parameter(lambda)) {
	}

	/**
	 * @brief Constructs a new distribution object.
	 * @param parameter The distribution parameter set.
	 */
	constexpr explicit ExponentialDistribution(Parameter const & parameter) : m_parameter(parameter) {
	}

	/**
	 * @brief Resets the internal state of the distribution.
	 */
	void reset() {
	}

	/**
	 * @brief Generates the next random number in the distribution.
	 * @tparam TGenerator Type of \p generator
	 * @param generator An uniform random bit generator object.
	 * @return The generated random number.
	 */
	template< typename TGenerator >
	auto operator()(TGenerator & generator) -> Result {
		return operator()(generator, m_parameter);
	}

	/**
	 * @brief Generates the next random number in the distribution.
	 * @tparam TGenerator Type of \p generator.
	 * @param generator An uniform random bit generator object.
	 * @param parameter Distribution parameter set to use instead of the associated one.
	 * @return The generated random number.
	 */
	template< typename TGenerator >
	auto operator()(TGenerator & generator, Parameter const & parameter) -> Result {
		return -log(Result(1) - generate_canonical<Result, FloatingPointTraits<Result>::digits >(generator)) / lambda();
	}

	/**
	 * @brief Returns the λ distribution parameter (rate of events).
	 * @return The λ distribution parameter (rate of events).
	 */
	constexpr auto lambda() const -> Result {
		return parameter().lambda();
	}

	/**
	 * @brief Returns the associated parameter set.
	 * @return The associated parameter set
	 */
	constexpr auto parameter() const -> Parameter {
		return m_parameter;
	}

	/**
	 * @brief Sets the associated parameter set to params.
	 * @param parameter New contents of the associated parameter set.
	 */
	void parameter(Parameter const & parameter) {
		m_parameter = parameter;
	}

	/**
	 * @brief Returns the minimum value potentially generated by the distribution.
	 * @return The minimum value potentially generated by the distribution.
	 */
	constexpr auto min() const -> Result {
		return 0;
	}

	/**
	 * @brief Returns the maximum value potentially generated by the distribution.
	 * @return The maximum value potentially generated by the distribution.
	 */
	constexpr auto max() const -> Result {
		return FloatingPointTraits<Result>::infinity();
	}

	/**
	 * @brief Compares to another distribution object for equality.
	 * @param y Another distribution objects to compare.
	 * @retval true The distribution objects are equal.
	 * @retval false Otherwise.
	 */
	constexpr auto operator==(ExponentialDistribution const & y) -> Boolean {
		return m_parameter == y.m_parameter;
	}

private:
	Parameter m_parameter;
}; // class ExponentialDistribution<TReal>

} // namespace Random
} // namespace BR