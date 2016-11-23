/**
 * @file
 * @brief adjacent_find
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/equal.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief like std::adjacent_find
 * @tparam TForwardIterator 前向迭代器类型
 * @tparam TBinaryPredicate 二元谓词类型
 * @param[in] first, last 输入区间
 * @param[in] predicate 二元谓词
 * @return
 */
template< typename TForwardIterator, typename TBinaryPredicate >
auto adjacent_find(TForwardIterator first, TForwardIterator last, TBinaryPredicate && predicate) -> TForwardIterator;

/**
 * @brief like std::adjacent_find
 * @tparam TForwardIterator 前向迭代器类型
 * @param[in] first, last 输入区间
 * @return
 */
template< typename TForwardIterator >
auto adjacent_find(TForwardIterator first, TForwardIterator last) -> TForwardIterator;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TForwardIterator, typename TBinaryPredicate >
auto adjacent_find(TForwardIterator first, TForwardIterator last, TBinaryPredicate && predicate) -> TForwardIterator {
	if (first != last) {
		for (auto i = first; ++i != last; first = i) {
			if (forward<TBinaryPredicate>(predicate)(*first, *i)) {
				return first;
			}
		}
	}
	return last;
}

template< typename TForwardIterator >
inline auto adjacent_find(TForwardIterator first, TForwardIterator last) -> TForwardIterator {
	return adjacent_find(first, last, Equal<>());
}

} // namespace Algorithm

} // namespace BR
