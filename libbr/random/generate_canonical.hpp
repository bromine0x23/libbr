/**
 * @file
 * @brief generate_canonical
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/max.hpp>
#include <libbr/algorithm/min.hpp>
#include <libbr/math/function/ilog2.hpp>
#include <libbr/type_traits/max_integer.hpp>
#include <libbr/type_traits/floating_point_traits.hpp>

namespace BR {

inline namespace Random {

/**
 * @brief generate_canonical
 * @tparam TReal
 * @tparam bits
 * @tparam TGenerator
 * @param generator
 * @return
 */
template< typename TReal, Size bits, typename TGenerator >
auto generate_canonical(TGenerator & generator) -> TReal {
	auto const digits = FloatingPointTraits<TReal>::digits;
	auto const b = digits < bits ? digits : bits;
	auto const log2_r = ilog2(generator.max() - generator.min() + UInt64(1)) + 1;
	auto const m = b / log2_r + (b % log2_r != 0) + (b == 0);
	auto const range = generator.max() - generator.min() + TReal(1);
	TReal sum = 0;
	TReal base = 1;
	for (Size i = 0; i < m; ++i) {
		sum += (generator() - generator.min()) * base;
		base *= range;
	}
	return sum / base;
}

} // namespace Random

} // namespace BR