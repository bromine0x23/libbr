/**
 * @file
 * @brief 一元函数对象基类
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/basic_functor.hpp>

namespace BR {
inline namespace Functional {

/**
 * @brief 一元函数对象基类
 * @tparam TArgument 参数类型
 */
template< typename TArgument >
struct UnaryFunctor : public BasicFunctor< TArgument > {
	constexpr UnaryFunctor() noexcept = default;
};

} // namespace Functional
} // namespace BR
