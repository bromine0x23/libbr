/**
 * @file
 * @brief rotate_copy
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::rotate_copy
 * @tparam TForwardIterator
 * @tparam TOutputIterator
 * @param[in] first,last
 * @param[in] middle
 * @param[out] result
 * @return
 */
template< typename TForwardIterator, typename TOutputIterator >
auto rotate_copy(TForwardIterator first, TForwardIterator middle, TForwardIterator last, TOutputIterator result) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TOutputIterator >
inline auto rotate_copy(TForwardIterator first, TForwardIterator middle, TForwardIterator last, TOutputIterator result) -> TOutputIterator {
	return copy(first, middle, copy(middle, last, result));
}

} // namespace Algorithm

} // namespace BR
