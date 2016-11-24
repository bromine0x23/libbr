/**
 * @file
 * @brief 等于比较
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::equal
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @tparam TBinaryPredicate
 * @param[in] first0,last0
 * @param[in] first1
 * @param[in] predicate
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TBinaryPredicate && predicate) -> bool;

/**
 * @brief like std::equal
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @param[in] first0,last0
 * @param[in] first1
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1 >
auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1) -> bool;

/**
 * @brief like std::equal
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @tparam TBinaryPredicate
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @param[in] predicate
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TBinaryPredicate && predicate) -> bool;

/**
 * @brief like std::equal
 * @tparam TInputIterator0
 * @tparam TInputIterator1
 * @param[in] first0,last0
 * @param[in] first1,last1
 * @return
 */
template< typename TInputIterator0, typename TInputIterator1 >
auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> bool;

} // namespace Algorithm



namespace Detail {
namespace Algorithm {

template< typename TSinglePassIterator0, typename TSinglePassIterator1, typename TBinaryPredicate >
inline auto equal(TSinglePassIterator0 first0, TSinglePassIterator0 last0, TSinglePassIterator1 first1, TSinglePassIterator1 last1, TBinaryPredicate && predicate, SinglePassTraversalTag, SinglePassTraversalTag) -> bool {
	for (; first0 != last0 && first1 != last1; ++first0, (void)++first1) {
		if (!forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
			return false;
		}
	}
	return first0 == last0 && first1 == last1;
}

template< typename TRandomAccessIterator0, typename TRandomAccessIterator1, typename TBinaryPredicate >
inline auto equal(TRandomAccessIterator0 first0, TRandomAccessIterator0 last0, TRandomAccessIterator1 first1, TRandomAccessIterator1 last1, TBinaryPredicate && predicate, RandomAccessTraversalTag, RandomAccessTraversalTag) -> bool {
	if (distance(first0, last0) != distance(first1, last1)) {
		return false;
	}
	return equal(first0, last0, first1, last1, forward<TBinaryPredicate>(predicate), SinglePassTraversalTag(), SinglePassTraversalTag());
}

} // namespace Algorithm
} // namespace Detail

inline namespace Algorithm {

template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TBinaryPredicate && predicate) -> bool {
	for (; first0 != last0; ++first0, (void)++first1) {
		if (!forward<TBinaryPredicate>(predicate)(*first0, *first1)) {
			return false;
		}
	}
	return true;
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1) -> bool {
	return equal(first0, last0, first1, Equal<>());
}

template< typename TInputIterator0, typename TInputIterator1, typename TBinaryPredicate >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1, TBinaryPredicate && predicate) -> bool {
	return Detail::Algorithm::equal(first0, last0, first1, last1, forward<TBinaryPredicate>(predicate), IteratorTraits<TInputIterator0>::category(), IteratorTraits<TInputIterator1>::category());
}

template< typename TInputIterator0, typename TInputIterator1 >
inline auto equal(TInputIterator0 first0, TInputIterator0 last0, TInputIterator1 first1, TInputIterator1 last1) -> bool {
	return equal(first0, last0, first1, last1, Equal<>());
}

} // namespace Algorithm

} // namespace BR
