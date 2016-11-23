/**
 * @file
 * @brief uninitialized_copy
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_trivial.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/boolean_constant.hpp>

namespace BR {

inline namespace Memory {

/**
 * @tparam TInputIterator
 * @tparam TForwardIterator
 * @param[in] first
 * @param[in] last
 * @param[out] result
 * @return
 */
template<typename TInputIterator, typename TForwardIterator>
auto uninitialized_copy(TInputIterator first, TInputIterator last, TForwardIterator result) -> TForwardIterator;

} // namespace Memory

namespace Detail {
namespace Memory {

template< typename TInputIterator, typename TForwardIterator >
inline auto uninitialized_copy(TInputIterator first, TInputIterator last, TForwardIterator result, BooleanTrue) -> TForwardIterator {
	return copy(first, last, result);
}

template< typename TInputIterator, typename TForwardIterator >
auto uninitialized_copy(TInputIterator first, TInputIterator last, TForwardIterator result, BooleanFalse) -> TForwardIterator {
	using Element = typename IteratorTraits<TForwardIterator>::Element;
	auto start = result;
#if !defined(BR_NO_EXCEPTIONS)
	try {
#endif
		for (; first != last; ++first, (void)++result) {
			new(address_of(result)) Element(first);
		}
#if !defined(BR_NO_EXCEPTIONS)
	} catch (...) {
		for (; start != result; ++start) {
			start->~Element();
		}
		throw;
	}
#endif
	return result;
}

template< typename TInputIterator, typename TForwardIterator >
inline auto uninitialized_copy(TInputIterator first, TInputIterator last, TForwardIterator result) -> TForwardIterator {
	return uninitialized_copy(
		first, last, result,
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
auto uninitialized_copy(TInputIterator first, TInputIterator last, TForwardIterator result) -> TForwardIterator {
	return Detail::Memory::uninitialized_copy(first, last, result);
}

} // namespace Memory

} // namespace BR