/**
 * @file
 * @brief replace_copy_if
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::replace_copy_if
 * @tparam TInputIterator
 * @tparam TOutputIterator
 * @tparam TValue
 * @tparam TUnaryPredicate
 * @param[in] first,last
 * @param[out] result
 * @param[in] new_value
 * @param[in] predicate
 * @return
 */
template< typename TInputIterator, typename TOutputIterator, typename TValue, typename TUnaryPredicate >
auto replace_copy_if(TInputIterator first, TInputIterator last, TOutputIterator result, TValue const & new_value, TUnaryPredicate && predicate) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TValue, typename TUnaryPredicate >
inline auto replace_copy_if(TInputIterator first, TInputIterator last, TOutputIterator result, TValue const & new_value, TUnaryPredicate && predicate) -> TOutputIterator {
	for (; first != last; ++first, (void) ++result) {
		*result = forward<TUnaryPredicate>(predicate)(*first) ? new_value : *first;
	}
	return result;
}

} // namespace Algorithm

} // namespace BR
