/**
 * @file
 * @brief shuffle
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::shuffle
 * @tparam TRandomAccessIterator
 * @tparam TUniformRandomNumberGenerator
 * @param[in,out] first,last
 * @param[in] generator
 * @todo implement it
 */
template< typename TRandomAccessIterator, typename TUniformRandomNumberGenerator >
void shuffle(TRandomAccessIterator first, TRandomAccessIterator last, TUniformRandomNumberGenerator && generator);

} // namespace Algorithm



inline namespace Algorithm {

template< typename TRandomAccessIterator, typename TUniformRandomNumberGenerator >
void shuffle(TRandomAccessIterator first, TRandomAccessIterator last, TUniformRandomNumberGenerator && generator) {
	// TODO
}

} // namespace Algorithm


} // namespace BR
