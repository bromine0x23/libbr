/**
 * @file
 * @brief fill_n
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/memory_fill.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conjunction.hpp>
#include <libbr/utility/enable_if.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Copy-assigns the given value to N elements in a range.
 * @tparam TOutputIterator Type of \p first which satisfies \em OutputIterator.
 * @tparam TSize Type of \p count
 * @tparam TValue Type of \p value
 * @param[in,out] first The beginning of the range of elements to modify.
 * @param[in] count Number of elements to modify.
 * @param[in] value The value to be assigned.
 * @return Iterator one past the last element assigned if count > 0, first otherwise.
 */
template< typename TOutputIterator, typename TSize, typename TValue >
constexpr auto fill_n(
	TOutputIterator first, TSize count,
	TValue const & value
) -> TOutputIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TOutputIterator, typename TSize, typename TValue >
constexpr inline auto fill_n(TOutputIterator first, TSize count, TValue const & value) -> TOutputIterator {
	for (; count > 0; ++first, (void)--count) {
		*first = value;
	}
	return first;
}

} // namespace Algorithms

} // namespace BR
