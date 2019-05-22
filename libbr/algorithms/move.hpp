/**
 * @file
 * @brief move
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/type_traits/has_trivial_copy_assignment.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_transform/remove_const.hpp>
#include <libbr/utility/conjunction.hpp>
#include <libbr/utility/enable_if.hpp>
#include <libbr/utility/transfer.hpp>

namespace BR {

inline namespace Algorithms {

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

} // namespace Algorithms



namespace _ {
namespace Algorithms {

template< typename TInputIterator, typename TOutputIterator >
auto move(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator {
	for (; first != last; ++first, (void)++result) {
		*result = transfer(*first);
	}
	return result;
}

template< typename TInputValue, typename TOutputValue, typename = EnableIf< Conjunction< IsSame< RemoveConst<TInputValue>, TOutputValue >, HasTrivialCopyAssignment<TInputValue> > > >
inline auto move(TInputValue * first, TInputValue * last, TOutputValue * result) -> TOutputValue * {
	auto n = static_cast<Size>(last - first);
	memory_copy(first, result, n * sizeof(TOutputValue));
	return result + n;
}

} // namespace Algorithms
} // namespace _

inline namespace Algorithms {

template< typename TInputIterator, typename TOutputIterator >
inline auto move(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator {
	return _::Algorithms::move(first, last, result);
}

} // namespace Algorithms

} // namespace BR
