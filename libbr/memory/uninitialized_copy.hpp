/**
 * @file
 * @brief uninitialized_copy
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/construct_at.hpp>
#include <libbr/memory/destroy.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_trivial.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Copies a range of objects to an uninitialized area of memory.
 *
 * Copies elements from the range \f$ [first, last) \f$ to an uninitialized memory area beginning at \p output.
 * @tparam TInputIterator Type of \p first & \p last which satisfies \em InputIterator.
 * @tparam TForwardIterator Type of \p output which satisfies \em ForwardIterator.
 * @param[in] first,last The range of the elements to copy.
 * @param[out] output The beginning of the destination range.
 * @return Iterator to the element past the last element copied.
 */
template<typename TInputIterator, typename TForwardIterator>
auto uninitialized_copy(
	TInputIterator first, TInputIterator last,
	TForwardIterator output
) -> TForwardIterator;

} // namespace Memory



namespace Detail {
namespace Memory {

template< typename TInputIterator, typename TForwardIterator >
inline auto uninitialized_copy(TInputIterator first, TInputIterator last, TForwardIterator output, BooleanTrue) -> TForwardIterator {
	return copy(first, last, output);
}

template< typename TInputIterator, typename TForwardIterator >
auto uninitialized_copy(TInputIterator first, TInputIterator last, TForwardIterator output, BooleanFalse) -> TForwardIterator {
	using BR::destroy;
	auto start = output;
	BR_TRY {
		for (; first != last; ++first, (void) ++output) {
			construct_at(address_of(*output), *first);
		}
	} BR_CATCH(...) {
		destroy(start, output);
		BR_RETHROW;
	}
	return output;
}

template< typename TInputIterator, typename TForwardIterator >
inline auto uninitialized_copy(TInputIterator first, TInputIterator last, TForwardIterator output) -> TForwardIterator {
	return uninitialized_copy(
		first, last, output,
		BooleanAnd<
			IsTrivial< typename IteratorTraits<TInputIterator>::Element >,
			IsTrivial< typename IteratorTraits<TForwardIterator>::Element >,
			IsAssignable<
				typename IteratorTraits<TForwardIterator>::Reference,
				typename IteratorTraits<TInputIterator>::Reference
			>
		>{}
	);
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TInputIterator, typename TForwardIterator >
inline auto uninitialized_copy(TInputIterator first, TInputIterator last, TForwardIterator output) -> TForwardIterator {
	return Detail::Memory::uninitialized_copy(first, last, output);
}

} // namespace Memory

} // namespace BR