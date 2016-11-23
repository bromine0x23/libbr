/**
 * @file
 * @brief uninitialized_fill
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/fill.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/has_copy_assignment.hpp>
#include <libbr/type_traits/is_trivial.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace Memory {

/**
 * @tparam TForwardIterator
 * @tparam TValue
 * @param[in,out] first
 * @param[in,out] last
 * @param value
 * @return
 */
template< typename TForwardIterator, typename TValue >
inline auto uninitialized_fill(TForwardIterator first, TForwardIterator last, TValue const & value) -> TForwardIterator;

} // namespace Memory

namespace Detail {
namespace Memory {

template< typename TForwardIterator, typename TValue >
inline auto uninitialized_fill(TForwardIterator first, TForwardIterator last, TValue const & value, BooleanTrue) -> TForwardIterator {
	return fill(first, last, value);
}

template< typename TForwardIterator, typename TValue >
auto uninitialized_fill(TForwardIterator first, TForwardIterator last, TValue const & value, BooleanFalse) -> TForwardIterator {
	using Element = typename IteratorTraits<TForwardIterator>::Element;
	auto start = first;
#if !defined(BR_NO_EXCEPTIONS)
	try {
#endif
		for (; first != last; ++first) {
			new(address_of(first)) Element(value);
		}
#if !defined(BR_NO_EXCEPTIONS)
	} catch (...) {
		for (; start != first; ++start) {
			start->~Element();
		}
		throw;
	}
#endif
	return first;
}

template< typename TForwardIterator, typename TValue >
inline auto uninitialized_fill(TForwardIterator first, TForwardIterator last, TValue const & value) -> TForwardIterator {
	return uninitialized_fill(first, last, value, BooleanAnd< IsTrivial<TValue>, HasCopyAssignment<TValue> >{});
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TForwardIterator, typename TValue >
auto uninitialized_fill(TForwardIterator first, TForwardIterator last, TValue const & value) -> TForwardIterator {
	return Detail::Memory::uninitialized_fill(first, last, value);
}
} // namespace Memory

} // namespace BR