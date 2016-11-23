/**
 * @file
 * @brief is_partitioned
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::is_partitioned
 * @tparam TInputIterator
 * @tparam TUnaryPredicate
 * @param[in] first,last
 * @param[in] predicate
 * @return
 */
template< typename TInputIterator, typename TUnaryPredicate >
auto is_partitioned(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> bool;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TUnaryPredicate >
auto is_partitioned(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> bool {
	for (; first != last; ++first) {
		if (!forward<TUnaryPredicate>(predicate)(*first)) {
			break;
		}
	}
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			return false;
		}
	}
	return true;
}

} // namespace Algorithm

} // namespace BR
