/**
 * @file
 * @brief replace_if
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::replace_if
 * @tparam TForwardIterator
 * @tparam TValue
 * @tparam TUnaryPredicate
 * @param[in,out] first,last
 * @param[in] new_value
 * @param[in] predicate
 */
template< typename TForwardIterator, typename TValue, typename TUnaryPredicate >
void replace_if(TForwardIterator first, TForwardIterator last, TValue const & new_value, TUnaryPredicate && predicate);

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TValue, typename TUnaryPredicate >
inline void replace_if(TForwardIterator first, TForwardIterator last, TValue const & new_value, TUnaryPredicate && predicate) {
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			*first = new_value;
		}
	}
}

} // namespace Algorithm

} // namespace BR
