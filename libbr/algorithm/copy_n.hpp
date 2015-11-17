/**
 * @file
 * @brief copy_n
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

namespace Detail {
namespace Algorithm {

template< typename TInputIterator, typename TSize, typename TOutputIterator >
auto copy_n(TInputIterator first, TSize n, TOutputIterator result, SinglePassTraversalTag) -> TOutputIterator {
	if (n > 0) {
		*result = *first;
		++result;
		for (--n; n > 0; --n) {
			*result = *++first;
			++result;
		}
	}
	return result;
}

template< typename TInputIterator, typename TSize, typename TOutputIterator >
inline auto copy_n(TInputIterator first, TSize n, TOutputIterator result, RandomAccessTraversalTag) -> TOutputIterator {
	return copy(first, first + n, result);
}

} // namespace Algorithm
} // namespace Detail

template< typename TInputIterator, typename TSize, typename TOutputIterator >
inline auto copy_n(TInputIterator first, TSize n, TOutputIterator result) -> TOutputIterator {
	return Detail::Algorithm::copy_n(first, n, result, IteratorTraits<TInputIterator>::category());
}

} // namespace BR
