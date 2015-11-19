/**
 * @file
 * @brief any_of
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

/**
 * @brief 检查区间内的是否有元素满足给定谓词
 * @param[in] first, last 待检查区间
 * @param[in] predicate 一元谓词
 */
template< typename TInputIterator, typename TUnaryPredicate >
inline auto any_of(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> bool {
	for (; first != last; ++first) {
		if (predicate(*first)) {
			return true;
		}
	}
	return false;
}

} // namespace BR
