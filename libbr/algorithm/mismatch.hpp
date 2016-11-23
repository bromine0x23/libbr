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
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::mismatch
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @tparam TBinaryPredicate
 * @param[in] first0,last0
 * @param[in] first1
 * @param[in] predicate
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TBinaryPredicate && predicate) -> Pair< TInputIterator0, TInputIterator1 >;

/**
 * @brief like std::mismatch
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @param[in] first0,last0
 * @param[in] first1
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1 >
auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1) -> Pair< TInputIterator0, TInputIterator1 >;

/**
 * @brief like std::mismatch
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @tparam TBinaryPredicate
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @param[in] predicate
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TBinaryPredicate && predicate) -> Pair< TInputIterator0, TInputIterator1 >;

/**
 * @brief like std::mismatch
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1 >
auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> Pair< TInputIterator0, TInputIterator1 >;
} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
inline auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TBinaryPredicate && predicate) -> Pair< TInputIterator0, TInputIterator1 > {
	for (; first0 != last0; ++first0, (void) ++first1) {
		if (!forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
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
		if (!forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
			break;
		}
	}
	return make_pair(first0, first1);
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto mismatch(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> Pair< TInputIterator0, TInputIterator1 > {
	return mismatch(first0, last0, first1, last1, Equal<>());
}

} // namespace Algorithm

} // namespace BR
