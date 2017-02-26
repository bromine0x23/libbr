/**
 * @file
 * @brief generate_canonical
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/function/ilog2.hpp>
#include <libbr/type_traits/max_integer.hpp>

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
	constexpr auto digits = sizeof(TReal) * BIT_PER_CHAR;
	constexpr auto b = digits < bits ? digits : bits;
	constexpr auto log_r = ilog2(TGenerator::max() - TGenerator::min() + UInt64(1)) + 1;
	constexpr auto k = b / log_r + (b % log_r != 0) + (b == 0);
	auto range = TGenerator::max() - TGenerator::min() + TReal(1);
	auto base = range;
	TReal s = generator() - TGenerator::min();
	for (Size i = 1; i < k; ++i, base *= range) {
		s += (generator() - TGenerator::min()) * base;
	}
	return s / base;
}

} // namespace Random

} // namespace BR