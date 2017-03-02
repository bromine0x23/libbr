/**
 * @file
 * @brief generate
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Assigns the results of successive function calls to every element in a range.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TGenerator Type of \p generator.
 * @param[out] first,last The range of elements to generate.
 * @param[in] generator Generator function object that will be called.
 */
template< typename TForwardIterator, typename TGenerator >
void generate(
	TForwardIterator first, TForwardIterator last,
	TGenerator && generator
);

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
