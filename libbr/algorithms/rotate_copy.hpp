/**
 * @file
 * @brief rotate_copy
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithms/copy.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Copies and rotate a range of elements.
 *
 * Copies the elements from the range \f$ [first, last) \f$ to another range beginning at \p output in such a way,
 * that the element \p middle becomes the first element of the new range and \f$ middle-1 \f$ becomes the last element.
 * @tparam TForwardIterator Type of \p first, \p middle & \p last which satisfies \em ForwardIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em ForwardIterator.
 * @param[in] first,last The range of elements to copy.
 * @param[in] middle The element that should appear at the beginning of the rotated range.
 * @param[out] output The beginning of the destination range.
 * @return Output iterator to the element past the last element copied.
 */
template< typename TForwardIterator, typename TOutputIterator >
auto rotate_copy(
	TForwardIterator first,
	TForwardIterator middle,
	TForwardIterator last,
	TOutputIterator output
) -> TOutputIterator;

} // namespace Algorithms



inline namespace Algorithms {

template< typename TForwardIterator, typename TOutputIterator >
inline auto rotate_copy(TForwardIterator first, TForwardIterator middle, TForwardIterator last, TOutputIterator result) -> TOutputIterator {
	return copy(first, middle, copy(middle, last, result));
}

} // namespace Algorithms

} // namespace BR
