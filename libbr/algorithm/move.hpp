/**
 * @file
 * @brief move
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/type_traits/boolean_and.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_trivial_copy_assignment.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/remove_const.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::move
 * @tparam TInputIterator
 * @tparam TOutputIterator
 * @param[in] first,last
 * @param[out] result
 * @return
 */
template< typename TInputIterator, typename TOutputIterator >
auto move(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TInputIterator, typename TOutputIterator >
auto move(TInputIterator first, TInputIterator last, TOutputIterator result) -> TOutputIterator {
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
