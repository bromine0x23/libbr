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

inline namespace Functional {

/**
 *
 * @tparam TArguments
 */
template< typename ... TArguments >
struct BasicFunctor {
	using Arguments = Types< TArguments... >;

	constexpr static SInt arity = sizeof...(TArguments);

	constexpr BasicFunctor() noexcept = default;
};

} // namespace Functional

} // namespace BR
