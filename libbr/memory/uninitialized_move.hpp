/**
 * @file
 * @brief uninitialized_move
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/move.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/construct_at.hpp>
#include <libbr/memory/destroy.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_trivial.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Moves a range of objects to an uninitialized area of memory.
 *
 * Moves elements from the range \f$ [first, last) \f$ to an uninitialized memory area beginning at \p output.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TForwardIterator Type of \p output which satisfies \em ForwardIterator.
 * @param[in] first,last The range of the elements to move.
 * @param[out] output The beginning of the destination range.
 * @return Iterator to the element past the last element moved.
 */
template<typename TInputIterator, typename TForwardIterator>
auto uninitialized_move(
	TInputIterator first, TInputIterator last,
	TForwardIterator output
) -> TForwardIterator;

} // namespace Memory



namespace Detail {
namespace Memory {

template< typename TInputIterator, typename TForwardIterator >
inline auto uninitialized_move(TInputIterator first, TInputIterator last, TForwardIterator output, BooleanTrue) -> TForwardIterator {
	return move(first, last, output);
}

template< typename TInputIterator, typename TForwardIterator >
auto uninitialized_move(TInputIterator first, TInputIterator last, TForwardIterator output, BooleanFalse) -> TForwardIterator {
	using BR::destroy;
	auto start = output;
	BR_TRY {
		for (; first != last; ++first, (void) ++output) {
			construct_at(address_of(*output), move(*first));
		}
	} BR_CATCH(...) {
		destroy(start, output);
		BR_RETHROW;
	}
	return output;
}

template< typename TInputIterator, typename TForwardIterator >
inline auto uninitialized_move(TInputIterator first, TInputIterator last, TForwardIterator output) -> TForwardIterator {
	return uninitialized_move(
		first, last, output,
		BooleanAnd<
			IsTrivial< typename IteratorTraits<TInputIterator>::Element >,
			IsTrivial< typename IteratorTraits<TForwardIterator>::Element >,
			IsAssignable<
				typename IteratorTraits<TForwardIterator>::Reference,
				typename IteratorTraits<TInputIterator>::Element
			>
		>{}
	);
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TInputIterator, typename TForwardIterator >
inline auto uninitialized_move(TInputIterator first, TInputIterator last, TForwardIterator output) -> TForwardIterator {
	return Detail::Memory::uninitialized_move(first, last, output);
}

} // namespace Memory

} // namespace BR