/**
 * @file
 * @brief each
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Applies a function to a range of elements.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TUnaryFunctor Type of \p functor
 * @param first,last The range to apply the function to.
 * @param functor Function object, to be applied to each elements in the range.
 * @return <code>forward&lt;TUnaryFunctor&gt;(functor)</code>
 */
template< typename TInputIterator, typename TUnaryFunctor >
auto each(TInputIterator first, TInputIterator last, TUnaryFunctor && functor) -> decltype(forward<TUnaryFunctor>(functor));

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TUnaryFunctor >
inline auto each(TInputIterator first, TInputIterator last, TUnaryFunctor && functor) -> decltype(forward<TUnaryFunctor>(functor)) {
	for (; first != last; ++first) {
		forward<TUnaryFunctor>(functor)(*first);
	}
	return forward<TUnaryFunctor>(functor);
}

} // namespace Algorithm

} // namespace BR
