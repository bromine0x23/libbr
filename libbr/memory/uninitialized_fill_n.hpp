/**
 * @file
 * @brief uninitialized_fill_n
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/fill_n.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/construct_at.hpp>
#include <libbr/memory/destroy.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/has_copy_assignment.hpp>
#include <libbr/type_traits/is_trivial.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Copies an object to an uninitialized area of memory, defined by a start and a count.
 *
 * Copies the given value \p value to the first \p count elements in an uninitialized memory area beginning at \p first.
 * @tparam TForwardIterator Type of \p first which satisfies \em ForwardIterator.
 * @tparam TSize Type of \p count.
 * @tparam TValue Type of \p value.
 * @param[in,out] first The beginning of the range of the elements to initialize.
 * @param count Number of elements to construct.
 * @param value The value to construct the elements with.
 * @return Iterator to the element past the last element copied.
 */
template< typename TForwardIterator, typename TSize, typename TValue >
auto uninitialized_fill_n(
	TForwardIterator first,
	TSize count,
	TValue const & value
) -> TForwardIterator;

} // namespace Memory


namespace Detail {
namespace Memory {

template< typename TForwardIterator, typename TSize, typename TValue >
inline auto uninitialized_fill_n(TForwardIterator first, TSize count, TValue const & value, BooleanTrue) -> TForwardIterator {
	return fill_n(first, count, value);
}

template< typename TForwardIterator, typename TSize, typename TValue >
auto uninitialized_fill_n(TForwardIterator first, TSize count, TValue const & value, BooleanFalse) -> TForwardIterator {
	using BR::destroy;
	auto current = first;
	BR_TRY {
		for (; count > 0; ++current, (void)--count) {
			construct_at(address_of(*current), value);
		}
	} BR_CATCH(...) {
		destroy(first, current);
		BR_RETHROW;
	}
	return current;
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TForwardIterator, typename TSize, typename TValue >
inline auto uninitialized_fill_n(TForwardIterator first, TSize count, TValue const & value) -> TForwardIterator {
	return Detail::Memory::uninitialized_fill_n(first, count, value, BooleanAnd< IsTrivial<TValue>, HasCopyAssignment<TValue> >{});
}

} // namespace Memory

} // namespace BR