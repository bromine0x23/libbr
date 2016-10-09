/**
 * @file
 * @brief copy
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/memory/memory_move.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/remove_const.hpp>
#include <libbr/type_traits/has_trivial_copy_assignment.hpp>
#include <libbr/type_traits/is_same.hpp>

namespace BR {

template< typename TInputIterator, typename TOutputIterator >
inline auto copy(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator;



namespace Detail {
namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator >
auto copy(TInputIterator first, TInputIterator last, TOutputIterator result, SinglePassTraversalTag) -> TOutputIterator {
	for ( ; first != last; ++result, ++first) {
		*result = *first;
	}
	return result;
}

template< typename TInputIterator, typename TOutputIterator >
auto copy(TInputIterator first, TInputIterator last, TOutputIterator result, RandomAccessTraversalTag) -> TOutputIterator {
	for (auto n = last - first; n > 0; --n) {
		*result = *first;
		++first;
		++result;
	}
	return result;
}

template< typename TInputIterator, typename TOutputIterator >
inline auto copy(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator {
	return copy(first, last, result, typename IteratorTraits<TInputIterator>::Category{});
}

template< typename TInputValue, typename TOutputValue, typename = EnableIf< BooleanAnd< IsSame< RemoveConst<TInputValue>, TOutputValue >, HasTrivialCopyAssignment<TInputValue> > > >
inline auto copy(TInputValue * first, TInputValue * last, TOutputValue * result) -> TOutputValue * {
	auto n = static_cast<Size>(last - first);
	memory_move(result, first, n * sizeof(TOutputValue));
	return result + n;
}

} // namespace Algorithm
} // namespace Detail

template< typename TInputIterator, typename TOutputIterator >
auto copy(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator {
	return Detail::Algorithm::copy(first, last, result);
}

} // namespace BR
