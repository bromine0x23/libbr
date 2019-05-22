/**
 * @file
 * @brief move_backward
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/type_traits/has_trivial_copy_assignment.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_transform/remove_const.hpp>
#include <libbr/utility/conjunction.hpp>
#include <libbr/utility/enable_if.hpp>
#include <libbr/utility/transfer.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Moves a range of elements to a new location in backwards order.
 *
 * Moves the elements from the range \f$ [first, last) \f$, to another range ending at \p output.
 * @tparam TBidirectionalIterator0 Type of \p first & \p last which satisfies \em BidirectionalIterator.
 * @tparam TBidirectionalIterator1 Type of \p output which satisfies \em BidirectionalIterator.
 * @param[in] first,last The range of the elements to move.
 * @param[out] output The end of the destination range.
 * @return Iterator in the destination range, pointing at the last element moved.
 */
template< typename TBidirectionalIterator0, typename TBidirectionalIterator1 >
auto move_backward(
	TBidirectionalIterator0 first, TBidirectionalIterator0 last,
	TBidirectionalIterator1 output
) -> TBidirectionalIterator1;

} // namespace Algorithms



namespace _ {
namespace Algorithms {

template< typename TBidirectionalIterator0, typename TBidirectionalIterator1 >
inline auto move_backward(TBidirectionalIterator0 first, TBidirectionalIterator0 last, TBidirectionalIterator1 output) -> TBidirectionalIterator1 {
	for (; first != last;) {
		*--output = transfer(*--last);
	}
	return output;
}

template< typename TInputValue, typename TOutputValue, typename = EnableIf< Conjunction< IsSame< RemoveConst<TInputValue>, TOutputValue >, HasTrivialCopyAssignment<TInputValue> > > >
inline auto move_backward(TInputValue * first, TInputValue * last, TOutputValue * output) -> TOutputValue * {
	auto const count = static_cast<Size>(last - first);
	if (count > 0) {
		output -= count;
		memory_copy(first, output, count * sizeof(TOutputValue));
	}
	return output;
}

} // namespace Algorithms
} // namespace _


inline namespace Algorithms {

template< typename TBidirectionalIterator0, typename TBidirectionalIterator1 >
inline auto move_backward(TBidirectionalIterator0 first, TBidirectionalIterator0 last, TBidirectionalIterator1 output) -> TBidirectionalIterator1 {
	return _::Algorithms::move_backward(first, last, output);
}

} // namespace Algorithms

} // namespace BR
