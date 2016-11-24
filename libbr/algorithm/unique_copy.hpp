/**
 * @file
 * @brief unique_copy
 * @author Bromine0x23
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
 * @brief like std::unique_copy
 * @tparam TInputIterator
 * @tparam TOutputIterator
 * @tparam TBinaryPredicate
 * @param[in] first,last
 * @param[out] result
 * @param[in] predicate
 * @return
 */
template< typename TInputIterator, typename TOutputIterator, typename TBinaryPredicate >
auto unique_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TBinaryPredicate && predicate) -> TOutputIterator;

/**
 * @brief like std::unique_copy
 * @tparam TInputIterator
 * @tparam TOutputIterator
 * @param[in] first,last
 * @param[out] result
 * @return
 */
template< typename TInputIterator, typename TOutputIterator >
auto unique_copy(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TBinaryPredicate >
auto unique_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TBinaryPredicate && predicate, SinglePassTraversalTag, IncrementableTraversalTag) -> TOutputIterator {
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
auto unique_copy(TForwardIterator first, TForwardIterator last, TOutputIterator result, TBinaryPredicate && predicate, ForwardTraversalTag, IncrementableTraversalTag) -> TOutputIterator {
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
auto unique_copy(TInputIterator first, TInputIterator last, TForwardIterator result, TBinaryPredicate && predicate, SinglePassTraversalTag, ForwardTraversalTag) -> TForwardIterator {
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
inline auto unique_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TBinaryPredicate && predicate) -> TOutputIterator {
	return Detail::Algorithm::unique_copy(first, last, result, forward<TBinaryPredicate>(predicate), typename IteratorTraits<TInputIterator>::Category{}, typename IteratorTraits<TOutputIterator>::Category{});
}

template< typename TInputIterator, typename TOutputIterator >
inline auto unique_copy(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator {
	return unique_copy(first, last, result, Equal<>());
}

} // namespace Algorithm

} // namespace BR
