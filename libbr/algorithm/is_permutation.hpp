/**
 * @file
 * @brief is_permutation
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Determines if a sequence is a permutation of another sequence.
 * @tparam TForwardIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TForwardIterator1 Type of \p first1 which satisfies \em ForwardIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param first0,last0 The range of elements to compare.
 * @param first1 The beginning of the second range to compare.
 * @param predicate Binary predicate which returns ​<code>true</code> if the elements should be treated as equal.
 * @retval true The range \f$ [first_0, last_0) \f$ is a permutation of the range \f$ [first_1, first_1 + (last_0 - first_0)) \f$.
 * @retval false Otherwise.
 */
template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto is_permutation(
	TForwardIterator0 first0, TForwardIterator0 last0,
	TForwardIterator1 first1,
	TBinaryPredicate && predicate
) -> Boolean;

/**
 * @brief Determines if a sequence is a permutation of another sequence.
 * @tparam TForwardIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TForwardIterator1 Type of \p first1 which satisfies \em ForwardIterator.
 * @param first0,last0 The range of elements to compare.
 * @param first1 The beginning of the second range to compare.
 * @retval true The range \f$ [first_0, last_0) \f$ is a permutation of the range \f$ [first_1, first_1 + (last_0 - first_0)) \f$.
 * @retval false Otherwise.
 */
template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto is_permutation(
	TForwardIterator0 first0, TForwardIterator0 last0,
	TForwardIterator1 first1
) -> Boolean;

/**
 * @brief Determines if a sequence is a permutation of another sequence.
 * @tparam TForwardIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TForwardIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @tparam TBinaryPredicate Type of \p predicate.
 * @param first0,last0 The range of elements to compare.
 * @param first1,last1 The second range to compare.
 * @param predicate Binary predicate which returns ​<code>true</code> if the elements should be treated as equal.
 * @retval true The range \f$ [first_0, last_0) \f$ is a permutation of the range \f$ [first_1, last_1) \f$.
 * @retval false Otherwise.
 */
template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto is_permutation(
	TForwardIterator0 first0, TForwardIterator0 last0,
	TForwardIterator1 first1, TForwardIterator1 last1,
	TBinaryPredicate && predicate
) -> Boolean;

/**
 * @brief Determines if a sequence is a permutation of another sequence.
 * @tparam TForwardIterator0 Type of \p first0 & \p last0 which satisfies \em ForwardIterator.
 * @tparam TForwardIterator1 Type of \p first1 & \p last1 which satisfies \em ForwardIterator.
 * @param first0,last0 The range of elements to compare.
 * @param first1,last1 The second range to compare.
 * @retval true The range \f$ [first_0, last_0) \f$ is a permutation of the range \f$ [first_1, last_1) \f$.
 * @retval false Otherwise.
 */
template< typename TForwardIterator0, typename TForwardIterator1 >
auto is_permutation(
	TForwardIterator0 first0, TForwardIterator0 last0,
	TForwardIterator1 first1, TForwardIterator1 last1
) -> Boolean;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate && predicate, ForwardTraversalTag, ForwardTraversalTag) -> Boolean {
	using Difference0 = typename IteratorTraits<TForwardIterator0>::Difference;
	using Difference1 = typename IteratorTraits<TForwardIterator1>::Difference;
	for (; first0 != last0 && first1 != last1; ++first0, (void)++first1) {
		if (!forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
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
			if (forward<TBinaryPredicate>(predicate)(*j, *i)) {
				goto NEXT_ITERATION;
			}
		} {
			Difference0 c1 = 0;
			for (auto j = first1; j != last1; ++j) {
				if (forward<TBinaryPredicate>(predicate)(*i, *j)) {
					++c1;
				}
			}
			if (c1 == 0) {
				return false;
			}
			Difference0 c0 = 1;
			for (auto j = next(i); j != last0; ++j) {
				if (forward<TBinaryPredicate>(predicate)(*i, *j)) {
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

template< typename TRandomAccessIterator0, typename TRandomAccessIterator1, typename TBinaryPredicate >
inline auto is_permutation(TRandomAccessIterator0 first0, TRandomAccessIterator0 last0, TRandomAccessIterator1 first1, TRandomAccessIterator1 last1, TBinaryPredicate && predicate, RandomAccessTraversalTag, RandomAccessTraversalTag) -> Boolean {
	if (last0 - first0 != last1 - first1) {
		return false;
	}
	return is_permutation(first0, last0, first1, forward<TBinaryPredicate>(predicate));
}

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
inline auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate && predicate) -> Boolean {
	return is_permutation(first0, last0, first1, last1, forward<TBinaryPredicate>(predicate), typename IteratorTraits<TForwardIterator0>::Category{}, typename IteratorTraits<TForwardIterator1>::Category{});
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
inline auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TBinaryPredicate && predicate) -> Boolean {
	using Difference0 = typename IteratorTraits<TForwardIterator0>::Difference;
	for (; first0 != last0; ++first0, (void)++first1) {
		if (!forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
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
		for (auto j = first0; j != i; ++j) {
			if (forward<TBinaryPredicate>(predicate)(*j, *i)) {
				goto NEXT_ITERATION;
			}
		} {
			Difference0 c1 = 0;
			for (auto j = first1; j != last1; ++j) {
				if (forward<TBinaryPredicate>(predicate)(*i, *j)) {
					++c1;
				}
			}
			if (c1 == 0) {
				return false;
			}
			Difference0 c0 = 1;
			for (auto j = next(i); j != last0; ++j) {
				if (forward<TBinaryPredicate>(predicate)(*i, *j)) {
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

template< typename TForwardIterator0, typename TForwardIterator1 >
inline auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1) -> Boolean {
	return is_permutation(first0, last0, first1, Equal<>());
}

template< typename TForwardIterator0, typename TForwardIterator1, typename TBinaryPredicate >
inline auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1, TBinaryPredicate && predicate) -> Boolean {
	return Detail::Algorithm::is_permutation(first0, last0, first1, last1, forward<TBinaryPredicate>(predicate));
}

template< typename TForwardIterator0, typename TForwardIterator1 >
inline auto is_permutation(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1) -> Boolean {
	return is_permutation(first0, last0, first1, last1, Equal<>());
}

} // namespace Algorithm

} // namespace BR
