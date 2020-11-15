/**
 * @file
 * @brief copy_backward
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/type_traits/has_trivial_copy_assignment.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_transform/remove_const.hpp>
#include <libbr/utility/conjunction.hpp>
#include <libbr/utility/enable_if.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Copies a range of elements in backwards order.
 * @tparam TBidirectionalIterator Type of \p first & \p last which satisfies \em BidirectionalIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em BidirectionalIterator and \em OutputIterator.
 * @param[in] first,last The range of the elements to copy.
 * @param[out] output End of the destination range.
 * @return Iterator to the last element copied.
 */
template< typename TBidirectionalIterator, typename TOutputIterator >
auto copy_backward(
	TBidirectionalIterator first, TBidirectionalIterator last,
	TOutputIterator output
) -> TOutputIterator;

} // namespace Algorithm



namespace _::Algorithms {

template< typename TBidirectionalIterator, typename TOutputIterator >
constexpr inline auto copy_backward(TBidirectionalIterator first, TBidirectionalIterator last, TOutputIterator output) -> TOutputIterator {
	for (; first != last;) {
		*--output = *--last;
	}
	return output;
}

template< typename TInputValue, typename TOutputValue, typename = EnableIf< Conjunction< IsSame< RemoveConst<TInputValue>, TOutputValue >, HasTrivialCopyAssignment<TOutputValue> > > >
inline auto copy_backward(TInputValue * first, TInputValue * last, TOutputValue * output) -> TOutputValue * {
	auto const count = static_cast<Size>(last - first);
	if (count > 0) {
		output -= count;
		memory_copy(first, output, count * sizeof(TOutputValue));
	}
	return output;
}

} // namespace _::Algorithms

inline namespace Algorithms {

template< typename TBidirectionalIterator, typename TOutputIterator >
inline auto copy_backward(TBidirectionalIterator first, TBidirectionalIterator last, TOutputIterator output) -> TOutputIterator {
	return _::Algorithms::copy_backward(first, last, output);
}

} // namespace Algorithms

} // namespace BR
