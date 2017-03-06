/**
 * @file
 * @brief transform
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/swallow.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Applies the given function to a range and stores the result in another range, beginning at \p output.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @tparam TUnaryOperation Type of \p operation.
 * @param[in] first,last The range of elements to transform.
 * @param[out] output The beginning of the destination range, may be equal to first.
 * @param[in] operation Unary operation function object that will be applied.
 * @return Output iterator to the element past the last element transformed.
 */
template< typename TInputIterator, typename TOutputIterator, typename TUnaryOperation >
auto transform(
	TInputIterator first, TInputIterator last,
	TOutputIterator output,
	TUnaryOperation && operation
) -> TOutputIterator;

/**
 * @brief Applies the given function to a range and stores the result in another range, beginning at \p output.
 * @tparam TInputIterator0 Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @tparam TOperation Type of \p operation.
 * @tparam TInputIterators Type of \p additions which satisfies \em InputIterator.
 * @param[in] first,last The first range of elements to transform.
 * @param[out] output The beginning of the destination range, may be equal to first0 or first1.
 * @param[in] operation Operation function object that will be applied.
 * @param[in] additions The beginning of the other ranges of elements to transform.
 * @return Output iterator to the element past the last element transformed.
 */
template< typename TInputIterator, typename TOutputIterator, typename TOperation, typename ...TInputIterators >
auto transform(
	TInputIterator first, TInputIterator last,
	TOutputIterator output,
	TOperation && operation,
	TInputIterators... additions
) -> TOutputIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator, typename TUnaryOperation >
inline auto transform(TInputIterator first, TInputIterator last, TOutputIterator output, TUnaryOperation && operation) -> TOutputIterator {
	for (; first != last; ++first, (void)++output) {
		*output = forward<TUnaryOperation>(operation)(*first);
	}
	return output;
}

template< typename TInputIterator, typename TOutputIterator, typename TOperation, typename ...TInputIterators >
inline auto transform(TInputIterator first, TInputIterator last, TOutputIterator output, TOperation && operation, TInputIterators... additions) -> TOutputIterator {
	for (; first != last; ++first, (void)++output) {
		*output = forward<TOperation>(operation)(*first, *additions...);
		swallow(++additions...);
	}
	return output;
}

} // namespace Algorithm

} // namespace BR
