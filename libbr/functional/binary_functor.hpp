/**
 * @file
 * @brief 二元函数对象基类
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/basic_functor.hpp>

namespace BR {
inline namespace Functional {

/**
 * @brief 二元函数对象基类
 * @tparam TFirst,TSecond 参数类型
 */
template< typename TFirst, typename TSecond >
struct BinaryFunctor : public BasicFunctor< TFirst, TSecond > {
	constexpr BinaryFunctor() noexcept = default;
};

} // namespace Functional
} // namespace BR
