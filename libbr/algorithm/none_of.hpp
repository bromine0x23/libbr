/**
 * @file
 * @brief none_of
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::none_of
 * @tparam TInputIterator
 * @tparam TUnaryPredicate
 * @param[in] first,last
 * @param[in] predicate
 * @return
 */
template< typename TInputIterator, typename TUnaryPredicate >
auto none_of(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> bool;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TUnaryPredicate >
inline auto none_of(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> bool {
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			return false;
		}
	}
	return true;
}

} // namespace Algorithm

} // namespace BR
