/**
 * @file
 * @brief swap
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Swaps two ranges of elements.
 * @tparam TForwardIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TForwardIterator1 Type of \p first1 which satisfies \em ForwardIterator.
 * @param[in,out] first0,last0 The first range of elements to swap.
 * @param[in,out] first1 The beginning of the second range of elements to swap.
 * @return Iterator to the element past the last element exchanged in the range beginning with \p first1.
 */
template< typename TForwardIterator0, typename TForwardIterator1 >
auto swap(
	TForwardIterator0 first0, TForwardIterator0 last0,
	TForwardIterator1 first1
) -> TForwardIterator1;

/**
 * @brief Swaps two ranges of elements.
 * @tparam TForwardIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TForwardIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @param[in,out] first0,last0 The first range of elements to swap.
 * @param[in,out] first1,last1 The second range of elements to swap.
 * @return Iterator to the element past the last element exchanged in the range beginning with \p first1.
 */
template< typename TForwardIterator0, typename TForwardIterator1 >
auto swap(
	TForwardIterator0 first0, TForwardIterator0 last0,
	TForwardIterator1 first1, TForwardIterator1 last1
) -> TForwardIterator1;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TForwardIterator0, typename TForwardIterator1 >
inline auto swap(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1) -> TForwardIterator1 {
	using BR::Utility::swap;
	for(; first0 != last0; ++first0, (void)++first1) {
		swap(*first0, *first1);
	}
	return first1;
}

template< typename TForwardIterator0, typename TForwardIterator1 >
inline auto swap(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1) -> TForwardIterator1 {
	using BR::Utility::swap;
	for(; first0 != last0 && first1 != last1; ++first0, (void)++first1) {
		swap(*first0, *first1);
	}
	return first1;
}

} // namespace Algorithms

} // namespace BR
