/**
 * @file
 * @brief replace_if
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Replaces all elements satisfying specific criteria.
 *
 * Replaces all elements for which predicate \p predicate returns <code>true</code>.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TUnaryPredicate Type of \p predicate.
 * @tparam TValue Type of \p new_value.
 * @param[in,out] first,last The range of elements to process.
 * @param[in] predicate Unary predicate which returns <code>true</code> if the element value should be replaced.
 * @param[in] new_value The value to use as replacement.
 */
template< typename TForwardIterator, typename TUnaryPredicate, typename TValue >
void replace_if(
	TForwardIterator first, TForwardIterator last,
	TUnaryPredicate && predicate,
	TValue const & new_value
);

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TUnaryPredicate, typename TValue >
inline void replace_if(TForwardIterator first, TForwardIterator last, TUnaryPredicate && predicate, TValue const & new_value) {
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			*first = new_value;
		}
	}
}

} // namespace Algorithm

} // namespace BR
