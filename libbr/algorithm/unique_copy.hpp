/**
 * @file
 * @brief unique_copy
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/adjacent_find.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

namespace Detail {
namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TBinaryPredicate >
auto unique_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TBinaryPredicate & predicate, InputIteratorTag _dummy0, OutputIteratorTag _dummy1) -> TOutputIterator {
	if (first != last) {
		auto t = *first;
		*result = t;
		++result;
		for (;++first != last;) {
			if (!predicate(t, *first)) {
				t = *first;
				*result = t;
				++result;
			}
		}
	}
	return result;
}

template< typename TForwardIterator, typename TOutputIterator, typename TBinaryPredicate >
auto unique_copy(TForwardIterator first, TForwardIterator last, TOutputIterator result, TBinaryPredicate & predicate, ForwardIteratorTag _dummy0, OutputIteratorTag _dummy1) -> TOutputIterator {
	if (first != last) {
		auto i = first;
		*result = *i;
		++result;
		for (; ++first != last;) {
			if (!predicate(*i, *first)) {
				*result = *first;
				++result;
				i = first;
			}
		}
	}
	return result;
}

template< typename TInputIterator, typename TForwardIterator, typename TBinaryPredicate >
auto unique_copy(TInputIterator first, TInputIterator last, TForwardIterator result, TBinaryPredicate & predicate, InputIteratorTag _dummy0, ForwardIteratorTag _dummy1) -> TForwardIterator {
	if (first != last) {
		for (*result = *first; ++first != last; ) {
			if (!predicate(*result, *first)) {
				*++result = *first;
			}
		}
		++result;
	}
	return result;
}

} // namespace Algorithm
} // namespace Detail

template< typename TInputIterator, typename TOutputIterator, typename TBinaryPredicate >
inline auto unique_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TBinaryPredicate && predicate) -> TOutputIterator {
	return Detail::Algorithm::unique_copy(first, last, result, predicate);
}

template< typename TInputIterator, typename TOutputIterator >
inline auto unique_copy(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator {
	return unique_copy(first, last, result, Equal<>());
}

} // namespace BR
