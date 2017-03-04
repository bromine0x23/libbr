/**
 * @file
 * @brief all_of
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Checks if a \p predicate is <code>true</code> for all of the elements in a range.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TUnaryPredicate Type of \p predicate
 * @param first,last The range of elements to examine.
 * @param predicate Unary predicate.
 * @return Returns <code>true</code> if the range is empty.
 * @retval true Unary predicate \p predicate returns <code>true</code> for all elements in the range.
 * @retval false Otherwise.
 */
template<typename TInputIterator, typename TUnaryPredicate>
auto all_of(
	TInputIterator first, TInputIterator last,
	TUnaryPredicate && predicate
) -> Boolean;

} // namespace Algorithm



inline namespace Algorithm {

template<typename TInputIterator, typename TUnaryPredicate>
inline auto all_of(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> Boolean {
	for (; first != last; ++first) {
		if (!forward<TUnaryPredicate>(predicate)(*first)) {
			return false;
		}
	}
	return true;
}

} // namespace Algorithm

} // namespace BR
