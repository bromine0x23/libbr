/**
 * @file
 * @brief copy_while
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief copy_while
 * @tparam TInputIterator
 * @tparam TOutputIterator
 * @tparam TUnaryPredicate
 * @param[in] first,last
 * @param[out] result
 * @param[in] predicate
 * @return
 */
template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate >
auto copy_while(TInputIterator first, TInputIterator last, TOutputIterator result, TUnaryPredicate && predicate) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TUnaryPredicate >
inline auto copy_while(TInputIterator first, TInputIterator last, TOutputIterator result, TUnaryPredicate && predicate) -> TOutputIterator {
	for (; first != last && forward<TUnaryPredicate>(predicate)(*first); ++result, (void)++first) {
		*result = *first;
	}
	return result;
}

} // namespace Algorithm

} // namespace BR
