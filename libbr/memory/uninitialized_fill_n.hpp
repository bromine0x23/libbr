/**
 * @file
 * @brief uninitialized_fill_n
 * @author Bromine0x23
 * @since 2015/10/30
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

template< typename TForwardIterator, typename TSize, typename TValue >
auto uninitialized_fill_n(TForwardIterator first, TSize count, TValue const & value) -> TForwardIterator {
	using Element = typename IteratorTraits<TForwardIterator>::Element;
	auto start = first;
	try {
		for (; count > 0; ++first, (void)--count) {
			new(&*first) Element(value);
		}
	} catch (...) {
		for (; start != first; ++start) {
			start->~Element();
		}
		throw;
	}
	return first;
}

} // namespace BR