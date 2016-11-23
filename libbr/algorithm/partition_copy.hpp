/**
 * @file
 * @brief partition_copy
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::partition_copy
 * @tparam TForwardIterator
 * @tparam TOutputIterator0,TOutputIterator1
 * @tparam TUnaryPredicate
 * @param[in] first,last
 * @param[out] output_true
 * @param[out] output_false
 * @param[in] predicate
 * @return
 */
template< typename TForwardIterator, typename TOutputIterator0, typename TOutputIterator1, typename TUnaryPredicate >
auto partition_copy(TForwardIterator first, TForwardIterator last, TOutputIterator0 output_true, TOutputIterator1 output_false, TUnaryPredicate && predicate) -> Pair< TOutputIterator0, TOutputIterator1 >;

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
