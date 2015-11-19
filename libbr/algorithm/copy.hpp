/**
 * @file
 * @brief copy
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/memory_move.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/remove_const.hpp>
#include <libbr/type_traits/has_trivial_copy_assign.hpp>
#include <libbr/type_traits/is_same.hpp>

namespace BR {

template< typename TInputIterator, typename TOutputIterator >
inline auto copy(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator;

namespace Detail {
namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator >
inline auto copy(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator {
	for (; first != last; ++first, (void)++result) {
		*result = *first;
	}
	return result;
}

template< typename TInputValue, typename TOutputValue, typename _TDummy = EnableIf< BooleanAnd< IsSame< RemoveConst<TInputValue>, TOutputValue >, HasTrivialCopyAssign<TOutputValue> > > >
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
