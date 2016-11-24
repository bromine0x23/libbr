/**
 * @file
 * @brief copy_if
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::copy_if
 * @tparam TInputIterator
 * @tparam TOutputIterator
 * @tparam TUnaryPredicate
 * @param[in] first,last
 * @param[out] result
 * @param[in] predicate
 * @return
 */
template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate >
auto copy_if(TInputIterator first, TInputIterator last, TOutputIterator result, TUnaryPredicate && predicate) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate >
inline auto copy_if(TInputIterator first, TInputIterator last, TOutputIterator result, TUnaryPredicate && predicate) -> TOutputIterator {
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			*result = *first;
			++result;
		}
	}
	return result;
}

} // namespace Algorithm

} // namespace BR
