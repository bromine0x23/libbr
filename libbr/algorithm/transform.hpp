/**
 * @file
 * @brief transform
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::transform
 * @tparam TInputIterator
 * @tparam TOutputIterator
 * @tparam TUnaryOperation
 * @param[in] first,last
 * @param[out] result
 * @param[in] operation
 * @return
 */
template< typename TInputIterator, typename TOutputIterator, typename TUnaryOperation >
auto transform(TInputIterator first, TInputIterator last, TOutputIterator result, TUnaryOperation && operation) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TUnaryOperation >
inline auto transform(TInputIterator first, TInputIterator last, TOutputIterator result, TUnaryOperation && operation) -> TOutputIterator {
	for (; first != last; ++first, (void)++result) {
		*result = forward<TUnaryOperation>(operation)(*first);
	}
	return result;
}

} // namespace Algorithm

} // namespace BR
