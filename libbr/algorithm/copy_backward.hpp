/**
 * @file
 * @brief copy_backward
 * @author Bromine0x23
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

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::copy_backward
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @param[in] first,last
 * @param[out] result
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1 >
auto copy_backward(TInputIterator0 first, TInputIterator0 last, TInputIterator1 result) -> TInputIterator1;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TBidirectionalIterator0, typename TBidirectionalIterator1 >
inline auto copy_backward(TBidirectionalIterator0 first, TBidirectionalIterator0 last, TBidirectionalIterator1 result) -> TBidirectionalIterator1 {
	for (; first != last;) {
		*--result = *--last;
	}
	return result;
}

template< typename TInputValue, typename TOutputValue, typename = EnableIf< BooleanAnd< IsSame< RemoveConst<TInputValue>, TOutputValue >, HasTrivialCopyAssignment<TOutputValue> > > >
inline auto copy_backward(TInputValue * first, TInputValue * last, TOutputValue * result) -> TOutputValue * {
	auto n = static_cast<Size>(last - first);
	result -= n;
	memory_move(result, first, n * sizeof(TOutputValue));
	return result;
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1 >
inline auto copy_backward(TInputIterator0 first, TInputIterator0 last, TInputIterator1 result) -> TInputIterator1 {
	return Detail::Algorithm::copy_backward(first, last, result);
}

} // namespace Algorithm

} // namespace BR
