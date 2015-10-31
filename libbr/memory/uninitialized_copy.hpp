/**
 * @file
 * @brief uninitialized_copy
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_traits/iterator_traits.hpp>

namespace BR {

template< typename TInputIterator, typename TForwardIterator >
auto uninitialized_copy(TInputIterator first, TInputIterator last, TForwardIterator result) -> TForwardIterator {
	using Element = typename IteratorTraits<TForwardIterator>::Element;
	auto start = result;
	try {
		for (; first != last; ++first, (void)++result) {
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

extern template auto uninitialized_copy(NChar * first, NChar * last, NChar * result) -> NChar *;

} // namespace BR