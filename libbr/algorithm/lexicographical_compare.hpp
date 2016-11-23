/**
 * @file
 * @brief lexicographical_compare
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * lexicographical_compare
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @tparam TComparator
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @param[in] comparator
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1, typename TComparator >
auto lexicographical_compare(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TComparator && comparator) -> bool;

/**
 * lexicographical_compare
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1 >
auto lexicographical_compare(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> bool;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TComparator >
auto lexicographical_compare(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TComparator && comparator) -> bool {
	for (; first1 != last1; ++first0, (void)++first1) {
		if (first0 == last0) {
			return true;
		}
		if (forward<TComparator>(comparator)(*first0, *first1)) {
			return true;
		}
		if (forward<TComparator>(comparator)(*first1, *first0)) {
			return false;
		}
	}
	return false;
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto lexicographical_compare(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> bool {
	return lexicographical_compare(first0, last0, first1, last1, Less<>());
}

} // namespace Algorithm

} // namespace BR
