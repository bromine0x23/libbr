/**
 * @file
 * @brief mismatch
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/functional/equal.hpp>

namespace BR {

template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
inline auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TBinaryPredicate && predicate) -> Pair< TInputIterator0, TInputIterator1 > {
	for (; first0 != last0; ++first0, (void) ++first1) {
		if (!predicate(*first0, *first1)) {
			break;
		}
	}
	return make_pair(first0, first1);
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1) -> Pair< TInputIterator0, TInputIterator1 > {
	return mismatch(first0, last0, first1, Equal<void>());
}

template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
inline auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TBinaryPredicate && predicate) -> Pair< TInputIterator0, TInputIterator1 > {
	for (; first0 != last0 && first1 != last1; ++first0, (void)++first1) {
		if (!predicate(*first0, *first1)) {
			break;
		}
	}
	return make_pair(first0, first1);
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> Pair< TInputIterator0, TInputIterator1 > {
	return mismatch(first0, last0, first1, last1, Equal<>());
}


} // namespace BR
