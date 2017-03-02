/**
 * @file
 * @brief move_backward
 * @author Bromine0x23
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
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like move_backward
 * @tparam TBidirectionalIterator0
 * @tparam TBidirectionalIterator1
 * @param[in] first,last
 * @param[out] result
 * @return
 */
template< typename TBidirectionalIterator0, typename TBidirectionalIterator1 >
auto move_backward(TBidirectionalIterator0 first, TBidirectionalIterator0 last, TBidirectionalIterator1 result) -> TBidirectionalIterator1;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TBidirectionalIterator0, typename TBidirectionalIterator1 >
inline auto move_backward(TBidirectionalIterator0 first, TBidirectionalIterator0 last, TBidirectionalIterator1 output) -> TBidirectionalIterator1 {
	for (; first != last;) {
		*--output = move(*--last);
	}
	return output;
}

template< typename TInputValue, typename TOutputValue, typename = EnableIf< BooleanAnd< IsSame< RemoveConst<TInputValue>, TOutputValue >, HasTrivialCopyAssignment<TInputValue> > > >
inline auto move_backward(TInputValue * first, TInputValue * last, TOutputValue * output) -> TOutputValue * {
	auto const count = static_cast<Size>(last - first);
	if (count > 0) {
		output -= count;
		memory_move(output, first, count * sizeof(TOutputValue));
	}
	return output;
}

} // namespace Algorithm
} // namespace Detail


inline namespace Algorithm {

template< typename TBidirectionalIterator0, typename TBidirectionalIterator1 >
inline auto move_backward(TBidirectionalIterator0 first, TBidirectionalIterator0 last, TBidirectionalIterator1 output) -> TBidirectionalIterator1 {
	return Detail::Algorithm::move_backward(first, last, output);
}

} // namespace Algorithm

} // namespace BR
