/**
 * @file
 * @brief swap
 * @author Bromine0x23
 * @since 2015/10/27
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/adjacent_find.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

template< typename TForwardIterator0, typename TForwardIterator1 >
inline auto swap(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1) -> TForwardIterator1 {
	for(; first0 != last0; ++first0, (void)++first1) {
		swap(*first0, *first1);
	}
	return first1;
}

template< typename TForwardIterator0, typename TForwardIterator1 >
inline auto swap(TForwardIterator0 first0, TForwardIterator0 last0, TForwardIterator1 first1, TForwardIterator1 last1) -> TForwardIterator1 {
	for(; first0 != last0 && first1 != last1; ++first0, (void)++first1) {
		swap(*first0, *first1);
	}
	return first1;
}

} // namespace BR
