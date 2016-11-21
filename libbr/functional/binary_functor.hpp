/**
 * @file
 * @brief 二元函数对象基类
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/basic_functor.hpp>

namespace BR {

inline namespace Functional {

/**
 * @tparam TFirst
 * @tparam TSecond
 */
template< typename TFirst, typename TSecond >
struct BinaryFunctor : public BasicFunctor< TFirst, TSecond > {
	constexpr BinaryFunctor() noexcept = default;
};

} // namespace Functional

} // namespace BR
