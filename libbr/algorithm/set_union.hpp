/**
 * @file
 * @brief set_union
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief std::set_union
 * @tparam TInputIterator0,TInputIterator1
 * @tparam TOutputIterator
 * @tparam TComparator
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @param[out] result
 * @param[in] comparator
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
auto set_union(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result, TComparator && comparator) -> TOutputIterator;

/**
 * @brief std::set_union
 * @tparam TInputIterator0,TInputIterator1
 * @tparam TOutputIterator
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @param[out] result
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
auto set_union(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
auto set_union(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result, TComparator && comparator) -> TOutputIterator {
	for (; first0 != last0; ++result) {
		if (first1 == last1) {
			return copy(first0, last0, result);
		}
		if (forward<TComparator>(comparator)(*first1, *first0)) {
			*result = *first1;
			++first1;
		} else {
			*result = *first0;
			if (!forward<TComparator>(comparator)(*first0, *first1)) {
				++first1;
			}
			++first0;
		}
	}
	return copy(first1, last1, result);
}

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
inline auto set_union(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result) -> TOutputIterator {
	return set_union(first0, last0, first1, last1, result, Less<>());
}

} // namespace Algorithm

} // namespace BR
