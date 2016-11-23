/**
 * @file
 * @brief fill
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/memory/memory_set.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_integral.hpp>
#include <libbr/type_traits/is_same.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::fill_n
 * @tparam TOutputIterator
 * @tparam TValue
 * @tparam TSize
 * @param[in,out] first
 * @param[in] n
 * @param[in] value
 * @return
 */
template< typename TOutputIterator, typename TSize, typename TValue >
auto fill_n(TOutputIterator first, TSize n, TValue const & value) -> TOutputIterator;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TOutputIterator, typename TSize, typename TValue >
inline auto fill_n(TOutputIterator first, TSize n, TValue const & value) -> TOutputIterator {
	for (; n > 0; ++first, (void)--n) {
		*first = value;
	}
	return first;
}

template< typename TOutputValue, typename TSize, typename TValue, typename = EnableIf< BooleanAnd< IsIntegral<TOutputValue>, BooleanConstant< sizeof(TOutputValue) == 1 >, NotSame< TOutputValue, bool >, IsIntegral<TValue>, BooleanConstant< sizeof(TValue) == 1 > > > >
inline auto fill_n(TOutputValue * first, TSize n, TValue const & value) -> TOutputValue * {
	if (n > 0) {
		memory_set(first, value, n);
	}
	return first;
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TOutputIterator, typename TSize, typename TValue >
inline auto fill_n(TOutputIterator first, TSize n, TValue const & value) -> TOutputIterator {
	return Detail::Algorithm::fill_n(first, n, value);
}

} // namespace Algorithm

} // namespace BR
