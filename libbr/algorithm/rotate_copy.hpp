/**
 * @file
 * @brief rotate_copy
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>

namespace BR {

inline namespace Algorithm {

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

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TOutputIterator >
inline auto rotate_copy(TForwardIterator first, TForwardIterator middle, TForwardIterator last, TOutputIterator result) -> TOutputIterator {
	return copy(first, middle, copy(middle, last, result));
}

} // namespace Algorithm

} // namespace BR
