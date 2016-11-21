/**
 * @file
 * @brief accumulate
 * @author Bromine0x23
 * @since 2016/11/22
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Algorithm {

template< typename TInputIterator, typename TValue >
inline auto accumulate(TInputIterator first, TInputIterator last, TValue init) -> TValue {
	for (; first != last; ++first) {
		init = init + *first;
	}
	return init;
}

template< typename TInputIterator, typename TValue, typename TBinaryFunctor >
inline auto accumulate(TInputIterator first, TInputIterator last, TValue init, TBinaryFunctor functor) -> TValue {
	for (; first != last; ++first) {
		init = functor(init, *first);
	}
	return init;
}

} // namespace Algorithm

} // namespace BR