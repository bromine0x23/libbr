/**
 * @file
 * @brief is_permutation
 * @author Bromine0x23
 * @since 2015/10/29
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
inline auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TBinaryPredicate && predicate) -> bool;

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
inline auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1) -> bool {
	return is_permutation(first0, last0, first1, Equal<>());
}

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
inline auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate && predicate) -> bool;

template< typename TForwardIterator0, typename TForwardIterator1 >
inline auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1) -> bool {
	return is_permutation(first0, last0, first1, last1, Equal<>());
}

namespace Detail {
namespace Algorithm {

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TBinaryPredicate & predicate) -> bool {
	using Difference0 = typename IteratorTraits<TForwardIterator0>::Difference;
	for (; first0 != last0; ++first0, (void)++first1) {
		if (!predicate(*first0, *first1)) {
			goto NOT_DONE;
		}
	}
	return true;
NOT_DONE:;
	auto length0 = distance(first0, last0);
	if (length0 == Difference0(1)) {
		return false;
	}
	auto last1 = next(first1, length0);
	for (auto i = first0; i != last0; ++i) {
		for (auto j = first1; j != i; ++j) {
			if (predicate(*j, *i)) {
				goto NEXT_ITERATION;
			}
		} {
			Difference0 c1 = 0;
			for (auto j = first1; j != last1; ++j) {
				if (predicate(*i, *j)) {
					++c1;
				}
			}
			if (c1 == 0) {
				return false;
			}
			Difference0 c0 = 1;
			for (auto j = next(i); j != last0; ++j) {
				if (predicate(*i, *j)) {
					++c0;
				}
			}
			if (c0 != c1) {
				return false;
			}
		}
	NEXT_ITERATION:;
	}
	return true;
}

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate && predicate, ForwardTraversalTag) -> bool {
	using Difference0 = typename IteratorTraits<TForwardIterator0>::Difference;
	using Difference1 = typename IteratorTraits<TForwardIterator1>::Difference;
	for (; first0 != last0 && first1 != last1; ++first0, (void)++first1) {
		if (!predicate(*first0, *first1)) {
			goto NOT_DONE;
		}
	}
	return first0 == last0 && first1 == last1;
NOT_DONE:;
	Difference0 length0 = distance(first0, last0);
	Difference1 length1 = distance(first1, last1);

	if (length0 != length1) {
		return false;
	}

	for (auto i = first0; i != last0; ++i) {
		for (auto j = first0; j != i; ++j) {
			if (predicate(*j, *i)) {
				goto __next_iter;
			}
		} {
			Difference0 c1 = 0;
			for (auto j = first1; j != last1; ++j) {
				if (predicate(*i, *j)) {
					++c1;
				}
			}
			if (c1 == 0) {
				return false;
			}
			Difference0 c0 = 1;
			for (auto j = next(i); j != last0; ++j) {
				if (predicate(*i, *j)) {
					++c0;
				}
			}
			if (c0 != c1) {
				return false;
			}
		}
	NEXT_ITERATION:;
	}
	return true;
}

template< typename TRandomAccessIteratorTag0, typename TRandomAccessIteratorTag1, typename TBinaryPredicate >
inline auto is_permutation(TRandomAccessIteratorTag0 first0, TRandomAccessIteratorTag0 last0, TRandomAccessIteratorTag1 first1, TRandomAccessIteratorTag1 last1, TBinaryPredicate && predicate, RandomAccessTraversalTag) -> bool {
	if (last0 - first0 != last1 - first1) {
		return false;
	}
	return is_permutation(first0, last0, first1, predicate);
}

} // namespace Algorithm
} // namespace Detail

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TBinaryPredicate && predicate) -> bool {
	return Detail::Algorithm::is_permutation(first0, last0, first1, predicate);
}

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate && predicate) -> bool {
	return Detail::Algorithm::is_permutation(first0, last0, first1, last1, predicate);
}

} // namespace BR
