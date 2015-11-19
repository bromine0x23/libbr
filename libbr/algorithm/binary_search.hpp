/**
 * @file
 * @brief binary_search
 * @author Bromine0x23
 * @since 2015/10/28
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/lower_bound.hpp>
#include <libbr/functional/less.hpp>

namespace BR {

/**
 * @brief 二分查找给定区间是否存在给定值
 * @param[in] first, last 待检查区间
 * @param[in] value 待查找值
 * @param[in] comparator 比较器
 */
template< typename TForwardIterator, typename TValue, typename TComparator >
inline auto binary_search(TForwardIterator first, TForwardIterator last, TValue const & value, TComparator && comparator) -> bool {
	first = lower_bound(first, last, value, comparator);
	return first != last && !comparator(value, *first);
}

/**
 * @brief 二分查找，使用Less<>作比较器
 * @param[in] first, last 待检查区间
 * @param[in] value 待查找值
 */
template< typename TForwardIterator, typename TValue >
inline auto binary_search(TForwardIterator first, TForwardIterator last, TValue const & value) -> bool {
	return binary_search(first, last, value, Less<>());
}

} // namespace BR
