/**
 * @file
 * @brief count
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::count_if
 * @tparam TInputIterator
 * @tparam TUnaryPredicate
 * @param[in] first,last
 * @param[in] predicate
 * @return
 */
template< typename TInputIterator, typename TUnaryPredicate >
auto count_if(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> typename IteratorTraits<TInputIterator>::Difference;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TUnaryPredicate >
inline auto count_if(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> typename IteratorTraits<TInputIterator>::Difference {
	typename IteratorTraits<TInputIterator>::Difference result(0);
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			++result;
		}
	}
	return result;
}

} // namespace Algorithm

} // namespace BR
