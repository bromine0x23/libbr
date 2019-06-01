/**
 * @file
 * @brief search_repeated
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/iterators/categories.hpp>
#include <libbr/iterators/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithms {

/**
 * @brief Searches the range \f$ [first, last) \f$ for the first sequence of \p count identical elements, each equal to the given value \p value.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TSize Type of \p count.
 * @tparam TValue Type of \p value.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param[in] first,last The range of elements to examine.
 * @param[in] count The length of the sequence to search for.
 * @param[in] value The value of the elements to search for.
 * @param[in] predicate Binary predicate which returns <code>​true</code> if the elements should be treated as equal.
 * @return Iterator to the beginning of the found sequence in the range \f$ [first, last) \f$.
 *         If no such sequence is found, \p last is returned.
 */
template< typename TForwardIterator, typename TSize, typename TValue, typename TBinaryPredicate >
constexpr auto search_repeated(
	TForwardIterator first, TForwardIterator last,
	TSize count,
	TValue const & value,
	TBinaryPredicate && predicate
) -> TForwardIterator;

/**
 * @brief Searches the range \f$ [first, last) \f$ for the first sequence of \p count identical elements, each equal to the given value \p value.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TSize Type of \p count.
 * @tparam TValue Type of \p value.
 * @param[in] first,last The range of elements to examine.
 * @param[in] count The length of the sequence to search for.
 * @param[in] value The value of the elements to search for.
 * @return Iterator to the beginning of the fou1nd sequence in the range \f$ [first, last) \f$.
 *         If no such sequence is found, \p last is returned.
 */
template< typename TForwardIterator, typename TSize, typename TValue >
constexpr auto search_repeated(
	TForwardIterator first, TForwardIterator last,
	TSize count,
	TValue const & value
) -> TForwardIterator;

} // namespace Algorithms



namespace _ {
namespace Algorithms {

template< typename TForwardIterator, typename TSize, typename TValue, typename TBinaryPredicate >
constexpr auto search_repeated(TForwardIterator first, TForwardIterator last, TSize count, TValue const & value, TBinaryPredicate && predicate, ForwardTraversalTag) -> TForwardIterator {
	if (count <= 0) {
		return first;
	}
	for (;;) {
		for (;;++first) {
			if (first == last) {
				return last;
			}
			if (forward<TBinaryPredicate>(predicate)(*first, value)) {
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
			if (!forward<TBinaryPredicate>(predicate)(*i, value)) {
				first = i;
				++first;
				break;
			}
		}
	}
}

template< typename TForwardIterator, typename TSize, typename TValue, typename TBinaryPredicate >
constexpr auto search_repeated(TForwardIterator first, TForwardIterator last, TSize count, TValue const & value, TBinaryPredicate && predicate, RandomAccessTraversalTag) -> TForwardIterator {
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
			if (forward<TBinaryPredicate>(predicate)(*first, value)) {
				break;
			}
		}
		auto i = first;
		for (auto matched = TSize(0);;) {
			if (++matched == count) {
				return first;
			}
			++i;
			if (!forward<TBinaryPredicate>(predicate)(*i, value)) {
				first = i;
				++first;
				break;
			}
		}
	}
}

template< typename TForwardIterator, typename TSize, typename TValue, typename TBinaryPredicate >
constexpr inline auto search_repeated(TForwardIterator first, TForwardIterator last, TSize count, TValue const & value, TBinaryPredicate && predicate) -> TForwardIterator {
	return search_repeated(first, last, count, value, forward<TBinaryPredicate>(predicate), IteratorTraits<TForwardIterator>::iterator_category());
}

} // namespace Algorithms
} // namespace _

inline namespace Algorithms {

template< typename TForwardIterator, typename TSize, typename TValue, typename TBinaryPredicate >
constexpr inline auto search_repeated(TForwardIterator first, TForwardIterator last, TSize count, TValue const & value, TBinaryPredicate && predicate) -> TForwardIterator {
	return _::Algorithms::search_repeated(first, last, count, value, forward<TBinaryPredicate>(predicate));
}

template< typename TForwardIterator, typename TSize, typename TValue >
constexpr inline auto search_repeated(TForwardIterator first, TForwardIterator last, TSize count, TValue const & value) -> TForwardIterator {
	return search_repeated(first, last, count, value, Equal<>{});
}

} // namespace Algorithm

} // namespace BR
