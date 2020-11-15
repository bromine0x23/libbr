/**
 * @file
 * @brief uniquify_copy
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/iterators/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Creates a copy of some range of elements that contains no consecutive duplicates.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param[in] first,last The range of elements to process.
 * @param[out] output The beginning of the destination range.
 * @param[in] predicate Binary predicate which returns <code>​true</code> if the elements should be treated as equal.
 * @return Output iterator to the element past the last written element.
 */
template< typename TInputIterator, typename TOutputIterator, typename TBinaryPredicate >
auto uniquify_copy(
	TInputIterator first, TInputIterator last,
	TOutputIterator output,
	TBinaryPredicate && predicate
) -> TOutputIterator;

/**
 * @brief Creates a copy of some range of elements that contains no consecutive duplicates.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @param[in] first,last The range of elements to process.
 * @param[out] output The beginning of the destination range.
 * @return Output iterator to the element past the last written element.
 */
template< typename TInputIterator, typename TOutputIterator >
auto uniquify_copy(
	TInputIterator first, TInputIterator last,
	TOutputIterator output
) -> TOutputIterator;

} // namespace Algorithms



namespace _::Algorithms {

template< typename TInputIterator, typename TOutputIterator, typename TBinaryPredicate >
auto uniquify_copy(TInputIterator first, TInputIterator last, TOutputIterator output, TBinaryPredicate && predicate, SinglePassTraversalTag, IncrementableTraversalTag) -> TOutputIterator {
	if (first != last) {
		auto t = *first;
		*output = t;
		++output;
		for (;++first != last;) {
			if (!forward<TBinaryPredicate>(predicate)(t, *first)) {
				t = *first;
				*output = t;
				++output;
			}
		}
	}
	return output;
}

template< typename TForwardIterator, typename TOutputIterator, typename TBinaryPredicate >
auto uniquify_copy(TForwardIterator first, TForwardIterator last, TOutputIterator output, TBinaryPredicate && predicate, ForwardTraversalTag, IncrementableTraversalTag) -> TOutputIterator {
	if (first != last) {
		auto i = first;
		*output = *i;
		++output;
		for (; ++first != last;) {
			if (!forward<TBinaryPredicate>(predicate)(*i, *first)) {
				*output = *first;
				++output;
				i = first;
			}
		}
	}
	return output;
}

template< typename TInputIterator, typename TForwardIterator, typename TBinaryPredicate >
auto uniquify_copy(TInputIterator first, TInputIterator last, TForwardIterator output, TBinaryPredicate && predicate, ForwardTraversalTag, ForwardTraversalTag) -> TForwardIterator {
	if (first != last) {
		for (*output = *first; ++first != last; ) {
			if (!forward<TBinaryPredicate>(predicate)(*output, *first)) {
				*++output = *first;
			}
		}
		++output;
	}
	return output;
}

template< typename TInputIterator, typename TOutputIterator, typename TBinaryPredicate >
inline auto uniquify_copy(TInputIterator first, TInputIterator last, TOutputIterator output, TBinaryPredicate && predicate) -> TOutputIterator {
	return uniquify_copy(first, last, output, forward<TBinaryPredicate>(predicate), IteratorTraits<TInputIterator>::iterator_category(), IteratorTraits<TOutputIterator>::iterator_category());
}

} // namespace _::Algorithms

inline namespace Algorithms {

template< typename TInputIterator, typename TOutputIterator, typename TBinaryPredicate >
inline auto uniquify_copy(TInputIterator first, TInputIterator last, TOutputIterator output, TBinaryPredicate && predicate) -> TOutputIterator {
	return _::Algorithms::uniquify_copy(first, last, output, forward<TBinaryPredicate>(predicate));
}

template< typename TInputIterator, typename TOutputIterator >
inline auto uniquify_copy(TInputIterator first, TInputIterator last, TOutputIterator output) -> TOutputIterator {
	return uniquify_copy(first, last, output, Equal<>{});
}

} // namespace Algorithms

} // namespace BR
