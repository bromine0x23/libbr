/**
 * @file
 * @brief merge
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::merge
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @tparam TOutputIterator
 * @tparam TComparator
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @param[out] result
 * @param[in] comparator
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
auto merge(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result, TComparator && comparator) -> TOutputIterator;

/**
 * @brief like std::merge
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @tparam TOutputIterator
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @param[out] result
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
auto merge(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result) -> TOutputIterator;
} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
auto merge(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result, TComparator & comparator) -> TOutputIterator {
	for (; first0 != last0; ++result) {
		if (first1 == last1) {
			return copy(first0, last0, result);
		}
		if (forward<TComparator>(comparator)(*first1, *first0)) {
			*result = *first1;
			++first1;
		} else {
			*result = *first0;
			++first0;
		}
	}
	return copy(first1, last1, result);
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
inline auto merge(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result, TComparator && comparator) -> TOutputIterator {
	return Detail::Algorithm::merge(first0, last0, first1, last1, result, forward<TComparator>(comparator));
}

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
inline auto merge(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result) -> TOutputIterator {
	return merge(first0, last0, first1, last1, result, Less<void>());
}

} // namespace Algorithm

} // namespace BR
