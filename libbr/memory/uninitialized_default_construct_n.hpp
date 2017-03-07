/**
 * @file
 * @brief uninitialized_default_construct_n
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/default_construct_at.hpp>
#include <libbr/memory/destroy.hpp>
#include <libbr/type_traits/has_trivial_default_constructor.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Constructs objects by default-initialization in an uninitialized area of memory, defined by a start and a count.
 *
 * Constructs n objects of type typename IteratorTraits<TForwardIterator>::Element in the uninitialized storage beginning at \p first by default-initialization
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @param[in] first The beginning of the range of elements to initialize
 * @param count The number of elements to initialize.
 * @return Iterator to the element past the last element constructed.
 */
template< typename TForwardIterator, typename TSize >
auto uninitialized_default_construct_n(
	TForwardIterator first,
	TSize count
) -> TForwardIterator;

} // namespace Memory



inline namespace Memory {

template< typename TForwardIterator, typename TSize >
inline auto uninitialized_default_construct_n(TForwardIterator first, TSize count) -> TForwardIterator {
	auto current = first;
	BR_TRY {
		for (; count > 0; ++current, (void)--count) {
			default_construct_at(address_of(*current));
		}
	} BR_CATCH(...) {
		destroy(first, current);
		BR_RETHROW;
	}
	return current;
}

} // namespace Memory

} // namespace BR