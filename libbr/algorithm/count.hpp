/**
 * @file
 * @brief count
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::count
 * @tparam TInputIterator
 * @tparam TValue
 * @param[in] first,last
 * @param[in] value
 * @return
 */
template< typename TInputIterator, typename TValue >
auto count(TInputIterator first, TInputIterator last, TValue const & value) -> typename IteratorTraits<TInputIterator>::Difference;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TValue >
inline auto count(TInputIterator first, TInputIterator last, TValue const & value) -> typename IteratorTraits<TInputIterator>::Difference {
	typename IteratorTraits<TInputIterator>::Difference result(0);
	for (; first != last; ++first) {
		if (*first == value) {
			++result;
		}
	}
	return result;
}

} // namespace Algorithm

} // namespace BR
