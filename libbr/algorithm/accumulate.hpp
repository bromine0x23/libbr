/**
 * @file
 * @brief accumulate
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/plus.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::accumulate
 * @tparam TInputIterator
 * @tparam TValue
 * @tparam TBinaryFunctor
 * @param[in] first,last
 * @param[in] init
 * @param[in] functor
 * @return
 */
template< typename TInputIterator, typename TValue, typename TBinaryFunctor >
auto accumulate(TInputIterator first, TInputIterator last, TValue init, TBinaryFunctor functor) -> TValue;

/**
 * @brief like std::accumulate
 * @tparam TInputIterator
 * @tparam TValue
 * @param[in] first,last
 * @param[in] init
 * @return
 */
template< typename TInputIterator, typename TValue >
auto accumulate(TInputIterator first, TInputIterator last, TValue init) -> TValue;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TValue, typename TBinaryFunctor >
inline auto accumulate(TInputIterator first, TInputIterator last, TValue init, TBinaryFunctor functor) -> TValue {
	for (; first != last; ++first) {
		init = forward<TBinaryFunctor>(functor)(init, *first);
	}
	return init;
}

template< typename TInputIterator, typename TValue >
inline auto accumulate(TInputIterator first, TInputIterator last, TValue init) -> TValue {
	return accumulate(first, last, init, Plus<>());
}

} // namespace Algorithm

} // namespace BR