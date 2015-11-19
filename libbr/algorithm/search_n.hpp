/**
 * @file
 * @brief search_n
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

template< typename TForwardIterator, typename TSize, typename TValue, typename TBinaryPredicate >
inline auto search_n(TForwardIterator first, TForwardIterator last, TSize count, TValue const & value, TBinaryPredicate && predicate) -> TForwardIterator;

template< typename TForwardIterator, typename TSize, typename TValue >
inline auto search_n(TForwardIterator first, TForwardIterator last, TSize count, TValue const & value) -> TForwardIterator {
	return search_n(first, last, count, value, Equal<>());
}

namespace Detail {
namespace Algorithm {

template< typename TForwardIterator, typename TSize, typename TValue, typename TBinaryPredicate >
auto search_n(TForwardIterator first, TForwardIterator last, TSize count, TValue const & value, TBinaryPredicate & predicate, ForwardTraversalTag) -> TForwardIterator {
	if (count <= 0) {
		return first;
	}
	for (;;) {
		for (;;++first) {
			if (first == last) {
				return last;
			}
			if (predicate(*first, value)) {
				break;
			}
		}
		auto i = first;
		for (auto matched = TSize(0);;) {
			if (++matched == count) {
				return first;
			}
			if (++i == last) {
				return last;
			}
			if (!predicate(*i, value)) {
				first = i;
				++first;
				break;
			}
		}
	}
}

template< typename TForwardIterator, typename TSize, typename TValue, typename TBinaryPredicate >
auto search_n(TForwardIterator first, TForwardIterator last, TSize count, TValue const & value, TBinaryPredicate & predicate, RandomAccessTraversalTag) -> TForwardIterator {
	if (count <= 0) {
		return first;
	}
	auto const length = last - first;
	if (length < count) {
		return last;
	}
	for (auto const start = last - (count - 1);;) {
		for (;; ++first) {
			if (first >= start) {
				return last;
			}
			if (predicate(*first, value)) {
				break;
			}
		}
		auto i = first;
		for (auto matched = TSize(0);;) {
			if (++matched == count) {
				return first;
			}
			++i;
			if (!predicate(*i, value)) {
				first = i;
				++first;
				break;
			}
		}
	}
}

} // namespace Algorithm
} // namespace Detail

template< typename TForwardIterator, typename TSize, typename TValue, typename TBinaryPredicate >
auto search_n(TForwardIterator first, TForwardIterator last, TSize count, TValue const & value, TBinaryPredicate && predicate) -> TForwardIterator {
	return Detail::Algorithm::search_n(first, last, count, value, predicate, IteratorTraits<TForwardIterator>::category());
}

} // namespace BR
