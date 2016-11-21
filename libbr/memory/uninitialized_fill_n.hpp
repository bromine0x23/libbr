/**
 * @file
 * @brief uninitialized_fill_n
 * @author Bromine0x23
 * @since 2015/10/30
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/fill_n.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_traits/has_copy_assignment.hpp>
#include <libbr/type_traits/is_trivial.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace Memory {

/**
 *
 * @tparam TForwardIterator
 * @tparam TSize
 * @tparam TValue
 * @param[in,out] first
 * @param count
 * @param value
 * @return
 */
template< typename TForwardIterator, typename TSize, typename TValue >
inline auto uninitialized_fill_n(TForwardIterator first, TSize count, TValue const & value) -> TForwardIterator;

} // namespace Memory


namespace Detail {
namespace Memory {

template< typename TForwardIterator, typename TSize, typename TValue >
inline auto uninitialized_fill_n(TForwardIterator first, TSize count, TValue const & value, BooleanTrue) -> TForwardIterator {
	return fill_n(first, count, value);
}

template< typename TForwardIterator, typename TSize, typename TValue >
auto uninitialized_fill_n(TForwardIterator first, TSize count, TValue const & value, BooleanFalse) -> TForwardIterator {
	using Element = typename IteratorTraits<TForwardIterator>::Element;
	auto start = first;
#if !defined(BR_NO_EXCEPTIONS)
	try {
#endif
		for (; count > 0; ++first, (void)--count) {
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

template< typename TForwardIterator, typename TSize, typename TValue >
inline auto uninitialized_fill_n(TForwardIterator first, TSize count, TValue const & value) -> TForwardIterator {
	return uninitialized_fill_n(first, count, value, BooleanAnd< IsTrivial<TValue>, HasCopyAssignment<TValue> >{});
}

} // namespace Memory
} // namespace Detail

inline namespace Memory {

template< typename TForwardIterator, typename TSize, typename TValue >
auto uninitialized_fill_n(TForwardIterator first, TSize count, TValue const & value) -> TForwardIterator {
	return Detail::Memory::uninitialized_fill_n(first, count, value);
}

} // namespace Memory

} // namespace BR