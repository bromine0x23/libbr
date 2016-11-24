/**
 * @file
 * @brief find_first_of
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::find_first_of
 * @tparam TInputIterator
 * @tparam TForwardIterator
 * @tparam TBinaryPredicate
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @param predicate
 * @return
 */
template< typename TInputIterator, typename TForwardIterator, typename TBinaryPredicate >
auto find_first_of(TInputIterator first0, TInputIterator last0, TForwardIterator first1, TForwardIterator last1, TBinaryPredicate && predicate) -> TInputIterator;


/**
 * @brief like std::find_first_of
 * @tparam TInputIterator
 * @tparam TForwardIterator
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @return
 */
template< typename TInputIterator, typename TForwardIterator >
auto find_first_of(TInputIterator first0, TInputIterator last0, TForwardIterator first1, TForwardIterator last1) -> TInputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TForwardIterator, typename TBinaryPredicate >
auto find_first_of(TInputIterator first0, TInputIterator last0, TForwardIterator first1, TForwardIterator last1, TBinaryPredicate && predicate) -> TInputIterator {
	for (; first0 != last0; ++first0) {
		for (auto i = first1; i != last1; ++i) {
			if (forward<TBinaryPredicate>(predicate)(*first1, *i)) {
				return first0;
			}
		}
	}
	return last0;
}

template< typename TInputIterator, typename TForwardIterator >
inline auto find_first_of(TInputIterator first0, TInputIterator last0, TForwardIterator first1, TForwardIterator last1) -> TInputIterator {
	return find_first_of(first0, last0, first1, last1, Equal<>());
}

} // namespace Algorithm

} // namespace BR
