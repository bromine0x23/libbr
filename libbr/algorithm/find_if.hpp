/**
 * @file
 * @brief find_if
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::find_if
 * @tparam TInputIterator
 * @tparam TUnaryPredicate
 * @param[in] first,last
 * @param[in] predicate
 * @return
 */
template< typename TInputIterator, typename TUnaryPredicate >
auto find_if(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> TInputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TUnaryPredicate >
inline auto find_if(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> TInputIterator {
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			break;
		}
	}
	return first;
}

} // namespace Algorithm

} // namespace BR
