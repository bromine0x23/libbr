/**
 * @file
 * @brief each
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

template< typename TInputIterator, typename TUnaryFunctor >
inline auto each(TInputIterator first, TInputIterator last, TUnaryFunctor && functor) -> TUnaryFunctor {
	for (; first != last; ++first) {
		functor(*first);
	}
	return forward<TUnaryFunctor>(functor);
}

} // namespace BR
