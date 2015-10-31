/**
 * @file
 * @brief uninitialized_copy_n
 * @author Bromine0x23
 * @since 2015/10/30
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

template< typename TInputIterator, typename TSize, typename TForwardIterator >
auto uninitialized_copy_n(TInputIterator first, TSize count, TForwardIterator result) -> TForwardIterator {
	using Element = typename IteratorTraits<TForwardIterator>::Element;
	auto start = result;
	try {
		for (; count > 0; ++first, (void)++result, --count) {
			new(&*result) Element(*first);
		}
	} catch (...) {
		for (; start != result; ++start) {
			start->~Element();
		}
		throw;
	}
	return result;
}

} // namespace BR