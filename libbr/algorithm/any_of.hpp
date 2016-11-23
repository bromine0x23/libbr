/**
 * @file
 * @brief any_of
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

inline namespace Algorithm {

/**
 * @brief 检查区间内的是否有元素满足给定谓词
 * @tparam TInputIterator 输入迭代器类型
 * @tparam TUnaryPredicate 一元谓词类型
 * @param[in] first,last 输入区间
 * @param[in] predicate 一元谓词
 */
template< typename TInputIterator, typename TUnaryPredicate >
auto any_of(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> bool;

} // namespace Algorithm



inline namespace Algorithm {

template< typename TInputIterator, typename TUnaryPredicate >
inline auto any_of(TInputIterator first, TInputIterator last, TUnaryPredicate && predicate) -> bool {
	for (; first != last; ++first) {
		if (forward<TUnaryPredicate>(predicate)(*first)) {
			return true;
		}
	}
	return false;
}

} // namespace Algorithm

} // namespace BR
