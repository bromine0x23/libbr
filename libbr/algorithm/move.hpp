/**
 * @file
 * @brief move
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/memory_move.hpp>
#include <libbr/type_traits/boolean_and.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_trivial_copy_assignment.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/remove_const.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Moves a range of elements to a new location.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TOutputIterator Type of \p output which satisfies \em OutputIterator.
 * @param[in] first,last The range of elements to move.
 * @param[out] output The beginning of the destination range.
 *                    The behavior is undefined if \p output is within the range \f$ [first, last) \f$.
 * @return Output iterator to the element past the last element moved \f$ (output + (last - first)) \f$
 */
template< typename TInputIterator, typename TOutputIterator >
auto move(
	TInputIterator first, TInputIterator last,
	TOutputIterator output
) -> TOutputIterator;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator >
auto move(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator {
	using BR::move;
	for (; first != last; ++first, (void)++result) {
		*result = move(*first);
	}
	return result;
}

template< typename TInputValue, typename TOutputValue, typename = EnableIf< BooleanAnd< IsSame< RemoveConst<TInputValue>, TOutputValue >, HasTrivialCopyAssignment<TInputValue> > > >
inline auto move(TInputValue * first, TInputValue * last, TOutputValue * result) -> TOutputValue * {
	auto n = static_cast<Size>(last - first);
	memory_move(result, first, n * sizeof(TOutputValue));
	return result + n;
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator >
inline auto move(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator {
	return Detail::Algorithm::move(first, last, result);
}

} // namespace Algorithm

} // namespace BR
