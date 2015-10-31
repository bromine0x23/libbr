/**
 * @file
 * @brief 函数对象基类
 * @author Bromine0x23
 * @since 2015/10/24
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/types.hpp>

namespace BR {

template< typename ... TArguments >
struct BasicFunctor {
	using Arguments = Types< TArguments... >;

	constexpr static auto arity = sizeof...(TArguments);

	constexpr BasicFunctor() noexcept = default;
};

} // namespace BR
