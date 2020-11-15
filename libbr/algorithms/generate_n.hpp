/**
 * @file
 * @brief generate_n
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Assigns the results of successive function calls to N elements in a range
 * @tparam TOutputIterator Type of \p first which satisfies \em OutputIterator.
 * @tparam TSize Type of \p count.
 * @tparam TGenerator Type of \p generator.
 * @param[out] first The beginning of the range of elements to generate.
 * @param[in] count Number of the elements to generate.
 * @param[in] generator Generator function object that will be called.
 * @return Iterator one past the last element assigned if \f$ count > 0 \f$, or \p first otherwise.
 */
template< typename TOutputIterator, typename TSize, typename TGenerator >
constexpr auto generate_n(
	TOutputIterator first, TSize count,
	TGenerator && generator
) -> TOutputIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TOutputIterator, typename TSize, typename TGenerator >
constexpr inline auto generate_n(TOutputIterator first, TSize count, TGenerator && generator) -> TOutputIterator {
	for (; count > 0; ++first, (void)--count) {
		*first = forward<TGenerator>(generator)();
	}
	return first;
}

} // namespace Algorithms

} // namespace BR
