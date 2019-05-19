/**
 * @file
 * @brief each_n
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Applies a function object to the first \p count elements of a sequence.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TUnaryFunctor Type of \p functor
 * @param first The beginning of the range to apply the function to.
 * @param count The number of elements to apply the function to.
 * @param functor Function object, to be applied to each elements in the range.
 * @return \f$ first + count \f$
 */
template< typename TInputIterator, typename TSize, typename TUnaryFunctor >
auto each_n(
	TInputIterator first,
	TSize count,
	TUnaryFunctor && functor
) -> TInputIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TInputIterator, typename TSize, typename TUnaryFunctor >
inline auto each_n(TInputIterator first, TSize count, TUnaryFunctor && functor) -> TInputIterator {
	for (; count > 0; ++first, (void)--count) {
		forward<TUnaryFunctor>(functor)(*first);
	}
	return first;
}

} // namespace Algorithms

} // namespace BR
