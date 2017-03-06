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
	TOutputIterator result
) -> TOutputIterator;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TBinaryPredicate >
auto uniquify_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TBinaryPredicate && predicate, SinglePassTraversalTag, IncrementableTraversalTag) -> TOutputIterator {
	if (first != last) {
		auto t = *first;
		*result = t;
		++result;
		for (;++first != last;) {
			if (!forward<TBinaryPredicate>(predicate)(t, *first)) {
				t = *first;
				*result = t;
				++result;
			}
		}
	}
	return result;
}

template< typename TForwardIterator, typename TOutputIterator, typename TBinaryPredicate >
auto uniquify_copy(TForwardIterator first, TForwardIterator last, TOutputIterator result, TBinaryPredicate && predicate, ForwardTraversalTag, IncrementableTraversalTag) -> TOutputIterator {
	if (first != last) {
		auto i = first;
		*result = *i;
		++result;
		for (; ++first != last;) {
			if (!forward<TBinaryPredicate>(predicate)(*i, *first)) {
				*result = *first;
				++result;
				i = first;
			}
		}
	}
	return result;
}

template< typename TInputIterator, typename TForwardIterator, typename TBinaryPredicate >
auto uniquify_copy(TInputIterator first, TInputIterator last, TForwardIterator result, TBinaryPredicate && predicate, SinglePassTraversalTag, ForwardTraversalTag) -> TForwardIterator {
	if (first != last) {
		for (*result = *first; ++first != last; ) {
			if (!forward<TBinaryPredicate>(predicate)(*result, *first)) {
				*++result = *first;
			}
		}
		++result;
	}
	return result;
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TBinaryPredicate >
inline auto uniquify_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TBinaryPredicate && predicate) -> TOutputIterator {
	return Detail::Algorithm::uniquify_copy(first, last, result, forward<TBinaryPredicate>(predicate), typename IteratorTraits<TInputIterator>::Category{}, typename IteratorTraits<TOutputIterator>::Category{});
}

template< typename TInputIterator, typename TOutputIterator >
inline auto uniquify_copy(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator {
	return uniquify_copy(first, last, result, Equal<>());
}

} // namespace Algorithm

} // namespace BR
