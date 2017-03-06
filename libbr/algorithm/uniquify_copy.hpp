/**
 * @file
 * @brief uniquify_copy
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/adjacent_find.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Algorithm {

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

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

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
auto uniquify_copy(TInputIterator first, TInputIterator last, TForwardIterator output, TBinaryPredicate && predicate, SinglePassTraversalTag, ForwardTraversalTag) -> TForwardIterator {
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

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TBinaryPredicate >
inline auto uniquify_copy(TInputIterator first, TInputIterator last, TOutputIterator output, TBinaryPredicate && predicate) -> TOutputIterator {
	return Detail::Algorithm::uniquify_copy(first, last, output, forward<TBinaryPredicate>(predicate), typename IteratorTraits<TInputIterator>::Category{}, typename IteratorTraits<TOutputIterator>::Category{});
}

template< typename TInputIterator, typename TOutputIterator >
inline auto uniquify_copy(TInputIterator first, TInputIterator last, TOutputIterator output) -> TOutputIterator {
	return uniquify_copy(first, last, output, Equal<>());
}

} // namespace Algorithm

} // namespace BR
