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

inline namespace Algorithm {

/**
 * @brief like std::for_each
 * @tparam TInputIterator
 * @tparam TUnaryFunctor
 * @param[in] first,last
 * @param[in] functor
 * @return
 */
template< typename TInputIterator, typename TUnaryFunctor >
auto each(TInputIterator first, TInputIterator last, TUnaryFunctor && functor) -> TUnaryFunctor;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TUnaryFunctor >
inline auto each(TInputIterator first, TInputIterator last, TUnaryFunctor && functor) -> TUnaryFunctor {
	for (; first != last; ++first) {
		forward<TUnaryFunctor>(functor)(*first);
	}
	return forward<TUnaryFunctor>(functor);
}

} // namespace Algorithm

} // namespace BR
