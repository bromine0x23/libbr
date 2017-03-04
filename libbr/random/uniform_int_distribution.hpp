/**
 * @file
 * @brief UniformIntDistribution
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/type_traits/common.hpp>
#include <libbr/type_traits/integer_traits.hpp>
#include <libbr/type_traits/make_unsigned.hpp>
#include <libbr/math/function/is_power2.hpp>

namespace BR {
inline namespace Random {

template< typename TInt = SInt >
class UniformIntDistribution;

template< typename TInt >
class UniformIntDistribution : public EqualityComparable< UniformIntDistribution<TInt> > {
public:
	using Result = TInt;

	class Parameter : public EqualityComparable<Parameter> {
	public:
		using Distribution = UniformIntDistribution;

		constexpr explicit Parameter(Result a = 0, Result b = IntegerTraits<Result>::max()) : m_a(a), m_b(b) {
		}

		constexpr auto a() const -> Result { return m_a; }
		constexpr auto b() const -> Result { return m_b; }

		constexpr auto operator==(Parameter const & y) const -> Boolean {
			return m_a == y.m_a && m_b == y.m_b;
		}

	private:
		Result m_a;
		Result m_b;
	};

public:
	constexpr explicit UniformIntDistribution(Result a = 0, Result b = IntegerTraits<Result>::max()) : m_parameter(Parameter(a, b)) {
	}

	constexpr explicit UniformIntDistribution(Parameter const & parameter) : m_parameter(parameter) {
	}

	void reset() {
	}

	template< typename TGenerator >
	auto operator()(TGenerator & generator) -> Result {
		return operator()(generator, m_parameter);
	}

	template< typename TGenerator >
	auto operator()(TGenerator & generator, Parameter parameter) -> Result {
		using CommonResult = Common< typename TGenerator::Result, MakeUnsigned<Result> >;
		CommonResult const generator_min = generator.min();
		CommonResult const generator_max = generator.max();
		CommonResult const generator_range = generator.max() - generator.min();
		CommonResult const range = CommonResult(parameter.b()) - CommonResult(parameter.a());
		CommonResult result;
		if (generator_range > range) {
			CommonResult const extended_range = range + 1;
			CommonResult const scaling = generator_range / extended_range;
			CommonResult const door = extended_range * scaling;
			result = CommonResult(generator()) - generator_min;
			BR_ASSERT(result <= door);
			result /= scaling;
		} else if (generator_range < range) {
			CommonResult const extended_generator_range = generator_range + 1;
			CommonResult temp = extended_generator_range * operator()(generator, Parameter(0, range / extended_generator_range));
			result = temp + CommonResult(generator()) - generator_min;
			BR_ASSERT(temp <= result && result <= range);
		} else {
			result = CommonResult(generator()) - generator_min;
		}
		return result + parameter.a();
	}

	constexpr auto parameter() const -> Parameter {
		return m_parameter;
	}

	void parameter(Parameter const & parameter) {
		m_parameter = parameter;
	}

	constexpr auto a() const -> Result { return parameter().a(); }
	constexpr auto b() const -> Result { return parameter().b(); }

	constexpr auto min() const -> Result { return a(); }
	constexpr auto max() const -> Result { return b(); }

	constexpr auto operator==(Parameter const & y) const -> Boolean {
		return m_parameter == y.m_parameter;
	}

private:
	Parameter m_parameter;

}; // class UniformIntDistribution<TInt>

} // namespace Random
} // namespace BR
