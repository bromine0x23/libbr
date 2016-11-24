/**
 * @file
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>

namespace BR {

/**
 * @brief Duff's device ，用于加速循环
 * @param[in] size 循环次数
 * @param[in] functor 循环体（可调用对象）
 * @see https://en.wikipedia.org/wiki/Duff%27s_device
 * @see https://zh.wikipedia.org/wiki/%E8%BE%BE%E5%A4%AB%E8%AE%BE%E5%A4%87
 *
 * 但也不一定管用
 */
template< typename TFunctor >
inline void duff_device(Size size, TFunctor functor) {
	auto count = size >> 3;
	switch (size & 7) {
		default:
			BR_ASSERT(false);
			do {
				functor(); case 7:;
				functor(); case 6:;
				functor(); case 5:;
				functor(); case 4:;
				functor(); case 3:;
				functor(); case 2:;
				functor(); case 1:;
				functor(); case 0:;
			} while (count-- > 0);
	}
}

} // namespace BR
