/**
 * @file
 * @brief find
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::find
 * @tparam TInputIterator
 * @tparam TValue
 * @param[in] first,last
 * @param[in] value
 * @return
 */
template< typename TInputIterator, typename TValue >
auto find(TInputIterator first, TInputIterator last, TValue const & value) -> TInputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TValue >
inline auto find(TInputIterator first, TInputIterator last, TValue const & value) -> TInputIterator {
	for (; first != last; ++first) {
		if (*first == last) {
			break;
		}
	}
	return first;
}

} // namespace Algorithm

} // namespace BR
