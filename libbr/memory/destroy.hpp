/**
 * @file
 * @brief destroy
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/iterator_traits.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/destroy_at.hpp>
#include <libbr/type_traits/has_trivial_destructor.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Destroys a range of objects.
 *
 * Destroys the objects in the range \f$ [first, last) \f$.
 * @tparam TForwardIterator Type of \p first & \p last which satisfies \em ForwardIterator.
 * @param first,last The range of elements to destroy.
 */
template< typename TForwardIterator >
void destroy(
	TForwardIterator first, TForwardIterator last
);

} // namespace Memory



namespace Detail {
namespace Memory {

template< typename TForwardIterator >
inline void destroy(TForwardIterator first, TForwardIterator last, BooleanTrue) noexcept {
}

template< typename TForwardIterator >
inline void destroy(TForwardIterator first, TForwardIterator last, BooleanFalse) {
	for (; first != last; ++first) {
		destroy_at(address_of(*first));
	}
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TForwardIterator >
inline void destroy(TForwardIterator first, TForwardIterator last) {
	Detail::Memory::destroy(first, last, HasTrivialDestructor< typename IteratorTraits<TForwardIterator>::Element >{});
}

} // namespace Memory

} // namespace BR