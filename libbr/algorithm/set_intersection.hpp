/**
 * @file
 * @brief set_intersection
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::set_intersection
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
auto set_intersection(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result, TComparator && comparator) -> TOutputIterator;

/**
 * @brief like std::set_intersection
 * @tparam TInputIterator0,TInputIterator1
 * @tparam TOutputIterator
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @param[out] result
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
auto set_intersection(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator, typename TComparator >
auto set_intersection(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result, TComparator && comparator) -> TOutputIterator {
	for (; first0 != last0 && first1 != last1; ) {
		if (forward<TComparator>(comparator)(*first0, *first1)) {
			++first0;
		} else {
			if (!forward<TComparator>(comparator)(*first1, *first0)) {
				*result = *first0;
				++result;
				++first0;
			}
			++first1;
		}
	}
	return result;
}

template< typename TInputIterator0, typename TInputIterator1, typename TOutputIterator >
inline auto set_intersection(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TOutputIterator result) -> TOutputIterator {
	return set_intersection(first0, last0, first1, last1, result, Less<>());
}

} // namespace Algorithm

} // namespace BR
