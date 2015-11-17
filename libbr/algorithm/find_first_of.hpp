/**
 * @file
 * @brief find_first_of
 * @author Bromine0x23
 * @since 2015/11/14
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>

namespace BR {

namespace Detail {
namespace Algorithm {

template< typename TInputIterator, typename TForwardIterator, typename TBinaryPredicate >
auto find_first_of(TInputIterator first0, TInputIterator last0, TForwardIterator first1, TForwardIterator last1, TBinaryPredicate & predicate) -> TInputIterator {
	for (; first0 != last0; ++first0) {
		for (auto i = first1; i != last1; ++i) {
			if (predicate(*first1, *i)) {
				return first0;
			}
		}
	}
	return last0;
}

} // namespace Algorithm
} // namespace Detail

template< typename TInputIterator, typename TForwardIterator, typename TBinaryPredicate >
inline auto find_first_of(TInputIterator first0, TInputIterator last0, TForwardIterator first1, TForwardIterator last1, TBinaryPredicate && predicate) -> TInputIterator {
	return Detail::Algorithm::find_first_of(first0, last0, first1, last1, predicate);
}

template< typename TInputIterator, typename TForwardIterator >
inline auto find_first_of(TInputIterator first0, TInputIterator last0, TForwardIterator first1, TForwardIterator last1) -> TInputIterator {
	return find_first_of(first0, last0, first1, last1, Equal<>());
}


} // namespace BR
