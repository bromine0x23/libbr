/**
 * @file
 * @brief copy_backward
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/memory_move.hpp>
#include <libbr/type_traits/boolean_and.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_trivial_copy_assignment.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/remove_const.hpp>

namespace BR {

inline namespace Algorithm {

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



namespace Detail {
namespace Algorithm {

template< typename TBidirectionalIterator, typename TOutputIterator >
inline auto copy_backward(TBidirectionalIterator first, TBidirectionalIterator last, TOutputIterator output) -> TOutputIterator {
	for (; first != last;) {
		*--output = *--last;
	}
	return output;
}

template< typename TInputValue, typename TOutputValue, typename = EnableIf< BooleanAnd< IsSame< RemoveConst<TInputValue>, TOutputValue >, HasTrivialCopyAssignment<TOutputValue> > > >
inline auto copy_backward(TInputValue * first, TInputValue * last, TOutputValue * output) -> TOutputValue * {
	auto n = static_cast<Size>(last - first);
	output -= n;
	memory_move(output, first, n * sizeof(TOutputValue));
	return output;
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TBidirectionalIterator, typename TOutputIterator >
inline auto copy_backward(TBidirectionalIterator first, TBidirectionalIterator last, TOutputIterator output) -> TOutputIterator {
	return Detail::Algorithm::copy_backward(first, last, output);
}

} // namespace Algorithm

} // namespace BR
