/**
 * @file
 * @brief fill_n
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/memory_set.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_same.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief Copy-assigns the given value to N elements in a range.
 * @tparam TOutputIterator Type of \p first which satisfies \em OutputIterator.
 * @tparam TSize Type of \p count
 * @tparam TValue Type of \p value
 * @param[in,out] first The beginning of the range of elements to modify.
 * @param[in] count Number of elements to modify.
 * @param[in] value The value to be assigned.
 * @return Iterator one past the last element assigned if count > 0, first otherwise.
 */
template< typename TOutputIterator, typename TSize, typename TValue >
auto fill_n(
	TOutputIterator first, TSize count,
	TValue const & value
) -> TOutputIterator;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TOutputIterator, typename TSize, typename TValue >
inline auto fill_n(TOutputIterator first, TSize count, TValue const & value) -> TOutputIterator {
	for (; count > 0; ++first, (void)--count) {
		*first = value;
	}
	return first;
}

template< typename TOutputValue, typename TSize, typename TValue, typename = EnableIf< BooleanAnd< IsIntegral<TOutputValue>, BooleanConstant< sizeof(TOutputValue) == 1 >, NotSame< TOutputValue, bool >, IsIntegral<TValue>, BooleanConstant< sizeof(TValue) == 1 > > > >
inline auto fill_n(TOutputValue * first, TSize count, TValue const & value) -> TOutputValue * {
	if (count > 0) {
		memory_set(first, value, count);
	}
	return first;
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TOutputIterator, typename TSize, typename TValue >
inline auto fill_n(TOutputIterator first, TSize count, TValue const & value) -> TOutputIterator {
	return Detail::Algorithm::fill_n(first, count, value);
}

} // namespace Algorithm

} // namespace BR
