/**
 * @file
 * @brief remove_copy
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::remove_copy
 * @tparam TInputIterator
 * @tparam TOutputIterator
 * @tparam TValue
 * @param[in] first,last
 * @param[out] result
 * @param[in] value
 * @return
 */
template< typename TInputIterator, typename TOutputIterator, typename TValue >
auto remove_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TValue const & value) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TValue >
auto remove_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TValue const & value) -> TOutputIterator {
	for (; first != last; ++first) {
		if (!(*first == value)) {
			*result = *first;
			++result;
		}
	}
	return result;
}

} // namespace Algorithm

} // namespace BR
