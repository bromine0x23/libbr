/**
 * @file
 * @brief generate_n
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::generate_n
 * @tparam TOutputIterator
 * @tparam TSize
 * @tparam TGenerator
 * @param[out] first
 * @param[in] n
 * @param[in] generator
 */
template< typename TOutputIterator, typename TSize, typename TGenerator >
void generate_n(TOutputIterator first, TSize n, TGenerator && generator);

} // namespace Algorithm



inline namespace Algorithm {

template< typename TOutputIterator, typename TSize, typename TGenerator >
inline void generate_n(TOutputIterator first, TSize n, TGenerator && generator) {
	for (; n > 0; ++first, (void)--n) {
		*first = forward<TGenerator>(generator)();
	}
	return first;
}

} // namespace Algorithm

} // namespace BR
