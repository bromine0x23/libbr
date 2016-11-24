/**
 * @file
 * @brief generate
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::generate
 * @tparam TForwardIterator
 * @tparam TGenerator
 * @param[out] first,last
 * @param[in] generator
 */
template< typename TForwardIterator, typename TGenerator >
void generate(TForwardIterator first, TForwardIterator last, TGenerator && generator);

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TGenerator >
inline void generate(TForwardIterator first, TForwardIterator last, TGenerator && generator) {
	for (; first != last; ++first) {
		*first = forward<TGenerator>(generator)();
	}
}

} // namespace Algorithm

} // namespace BR
