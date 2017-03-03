/**
 * @file
 * @brief partition_copy
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Copies a range dividing the elements into two groups.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TOutputIterator0,TOutputIterator1 Type of \p output_true & \p output_false which satisfies \em OutputIterator.
 * @tparam TUnaryPredicate Type of \p predicate.
 * @param[in] first,last The range of elements to sort.
 * @param[out] output_true The beginning of the output range for the elements that satisfy \p predicate.
 * @param[out] output_false The beginning of the output range for the elements that do not satisfy \p predicate.
 * @param[in] predicate Unary predicate which returns ​<code>true</code> if the element should be placed in \p output_true.
 * @return A Pair constructed from the iterator to the end of the \p output_true range and the iterator to the end of the \p output_false range.
 */
template< typename TForwardIterator, typename TOutputIterator0, typename TOutputIterator1, typename TUnaryPredicate >
auto partition_copy(
	TForwardIterator first, TForwardIterator last,
	TOutputIterator0 output_true, TOutputIterator1 output_false,
	TUnaryPredicate && predicate
) -> Pair< TOutputIterator0, TOutputIterator1 >;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TOutputIterator0, typename TOutputIterator1, typename TUnaryPredicate >
auto partition_copy(TForwardIterator first, TForwardIterator last, TOutputIterator0 output_true, TOutputIterator1 output_false, TUnaryPredicate && predicate) -> Pair< TOutputIterator0, TOutputIterator1 > {
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			*output_true = *first;
			++output_true;
		} else {
			*output_false = *first;
			++output_false;
		}
	}
	return make_pair(output_true, output_false);
}

} // namespace Algorithm

} // namespace BR
