/**
 * @file
 * @brief uninitialized_fill
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

template< typename TForwardIterator, typename TValue >
auto uninitialized_fill(TForwardIterator first, TForwardIterator last, TValue const & value) -> TForwardIterator {
	using Element = typename IteratorTraits<TForwardIterator>::Element;
	auto start = first;
	try {
		for (; first != last; ++first) {
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