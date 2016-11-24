/**
 * @file
 * @brief replace_copy
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::replace_copy
 * @tparam TInputIterator
 * @tparam TOutputIterator
 * @tparam TValue
 * @param[in] first,last
 * @param[out] result
 * @param[in] old_value
 * @param[in] new_value
 * @return
 */
template< typename TInputIterator, typename TOutputIterator, typename TValue >
auto replace_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TValue const & old_value, TValue const & new_value) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TValue >
inline auto replace_copy(TInputIterator first, TInputIterator last, TOutputIterator result, TValue const & old_value, TValue const & new_value) -> TOutputIterator {
	for (; first != last; ++first, (void) ++result) {
		*result = (*first == old_value) ? new_value : *first;
	}
	return result;
}

} // namespace Algorithm

} // namespace BR
