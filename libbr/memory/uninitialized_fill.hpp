/**
 * @file
 * @brief uninitialized_fill
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/fill.hpp>
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
 * @brief Copies an object to an uninitialized area of memory, defined by a range.
 *
 * Copies the given value to an uninitialized memory area, defined by the range \f$ [first, last) \f$.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @tparam TValue Type of \p value.
 * @param[in,out] first,last The range of the elements to initialize
 * @param value The value to construct the elements with.
 */
template< typename TForwardIterator, typename TValue >
void uninitialized_fill(
	TForwardIterator first, TForwardIterator last,
	TValue const & value
);

} // namespace Memory



namespace Detail {
namespace Memory {

template< typename TForwardIterator, typename TValue >
void uninitialized_fill(TForwardIterator first, TForwardIterator last, TValue const & value, BooleanTrue) {
	fill(first, last, value);
}

template< typename TForwardIterator, typename TValue >
void uninitialized_fill(TForwardIterator first, TForwardIterator last, TValue const & value, BooleanFalse) {
	using BR::destroy;
	auto current = first;
	BR_TRY {
		for (; current != last; ++current) {
			construct_at(address_of(*current), value);
		}
	} BR_CATCH(...) {
		destroy(first, current);
		BR_RETHROW;
	}
}

template< typename TForwardIterator, typename TValue >
inline void uninitialized_fill(TForwardIterator first, TForwardIterator last, TValue const & value) {
	uninitialized_fill(first, last, value, BooleanAnd< IsTrivial<TValue>, HasCopyAssignment<TValue> >{});
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TForwardIterator, typename TValue >
inline void uninitialized_fill(TForwardIterator first, TForwardIterator last, TValue const & value) {
	Detail::Memory::uninitialized_fill(first, last, value);
}
} // namespace Memory

} // namespace BR