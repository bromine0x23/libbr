/**
 * @file
 * @brief copy
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/iterators/iterator_traits.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/type_traits/has_trivial_copy_assignment.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_transform/remove_const.hpp>
#include <libbr/utility/conjunction.hpp>
#include <libbr/utility/enable_if.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Copies a range of elements to a new location.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @param[in] first,last The range of elements to copy.
 * @param[out] output The beginning of the destination range.
 * @return Output iterator to the element in the destination range, one past the last element copied.
 */
template< typename TInputIterator, typename TOutputIterator >
auto copy(
	TInputIterator first, TInputIterator last,
	TOutputIterator output
) -> TOutputIterator;

} // namespace Algorithms



namespace _::Algorithms {

template< typename TSinglePassIterator, typename TOutputIterator >
auto copy(TSinglePassIterator first, TSinglePassIterator last, TOutputIterator output, SinglePassTraversalTag) -> TOutputIterator {
	for ( ; first != last; ++output, ++first) {
		*output = *first;
	}
	return output;
}

template< typename TRandomAccessIterator, typename TOutputIterator >
auto copy(TRandomAccessIterator first, TRandomAccessIterator last, TOutputIterator output, RandomAccessTraversalTag) -> TOutputIterator {
	for (auto count = last - first; count > 0; --count) {
		*output = *first;
		++first;
		++output;
	}
	return output;
}

template< typename TInputIterator, typename TOutputIterator >
inline auto copy(TInputIterator first, TInputIterator last, TOutputIterator output) -> TOutputIterator {
	return copy(first, last, output, IteratorTraits<TInputIterator>::iterator_category());
}

template< typename TInputValue, typename TOutputValue, typename = EnableIf< Conjunction< IsSame< RemoveConst<TInputValue>, TOutputValue >, HasTrivialCopyAssignment<TInputValue> > > >
inline auto copy(TInputValue * first, TInputValue * last, TOutputValue * output) -> TOutputValue * {
	auto const count = static_cast<USize>(last - first);
	if (count > 0) {
		memory_copy(first, output, count * sizeof(TOutputValue));
	}
	return output + count;
}

} // namespace _::Algorithms

inline namespace Algorithms {

template< typename TInputIterator, typename TOutputIterator >
inline auto copy(TInputIterator first, TInputIterator last, TOutputIterator output) -> TOutputIterator {
	return _::Algorithms::copy(first, last, output);
}

} // namespace Algorithms

} // namespace BR
