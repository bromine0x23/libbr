/**
 * @file
 * @brief search
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::search
 * @tparam TForwardIterator0,TForwardIterator1
 * @tparam TBinaryPredicate
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @param[in] predicate
 * @return
 */
template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto search(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate && predicate) -> TForwardIterator0;

/**
 * @brief like std::search
 * @tparam TForwardIterator0,TForwardIterator1
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @return
 */
template< typename TForwardIterator0, typename TForwardIterator1 >
auto search(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1) -> TForwardIterator0;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto search(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate && predicate, ForwardTraversalTag, ForwardTraversalTag) -> TForwardIterator0 {
	if (first1 == last1) {
		return first0;
	}
	for (;;) {
		for (;; ++first0) {
			if (first0 == last0) {
				return last0;
			}
			if (forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
				break;
			}
		}
		auto i0 = first0;
		auto i1 = first1;
		for (;;) {
			if (++i1 == last1) {
				return first0;
			}
			if (++i0 == last0) {
				return last0;
			}
			if (!forward<TBinaryPredicate>(predicate)(*i0, *i1)) {
				++first0;
				break;
			}
		}
	}
}

template< typename TRandomAccessIterator0, typename TRandomAccessIterator1, typename TBinaryPredicate >
auto search(TRandomAccessIterator0 first0, TRandomAccessIterator0 last0, TRandomAccessIterator1 first1, TRandomAccessIterator1 last1, TBinaryPredicate && predicate, RandomAccessTraversalTag, RandomAccessTraversalTag) -> TRandomAccessIterator0 {
	auto const length1 = last1 - first1;
	if (length1 == 0) {
		return first0;
	}
	auto const length0 = last0 - first0;
	if (length0 < length1) {
		return last0;
	}
	for (auto const start = first0 + (length1 - 1);;) {
		for (;; ++first0) {
			if (first0 == start) {
				return last0;
			}
			if (forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
				break;
			}
		}
		auto i0 = first0;
		auto i1 = first1;
		for (;;) {
			if (++i1 == last1) {
				return first0;
			}
			++i0;
			if (!forward<TBinaryPredicate>(predicate)(*i0, *i1)) {
				++first0;
				break;
			}
		}
	}
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
inline auto search(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate && predicate) -> TForwardIterator0 {
	return Detail::Algorithm::search(first0, last0, first1, last1, forward<TBinaryPredicate>(predicate), typename IteratorTraits<TForwardIterator0>::Category{}, typename IteratorTraits<TForwardIterator1>::Category{});
}

template< typename TForwardIterator0, typename TForwardIterator1 >
inline auto search(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1) -> TForwardIterator0 {
	return search(first0, last0, first1, last1, Equal<>());
}

} // namespace Algorithm

} // namespace BR
