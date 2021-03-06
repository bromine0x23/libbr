/**
 * @file
 * @brief 函数对象基类
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/type_sequence.hpp>

namespace BR {
inline namespace Functional {

/**
 * @brief 函数对象基类
 * @tparam TArguments 参数类型，void 表示范型
 */
template< typename... TArguments >
struct BasicFunctor {
	/**
	 * @brief 参数类型，void 表示范型
	 */
	using Arguments = TypeSequence< TArguments... >;

	/**
	 * @brief 元数，负数 -n 表示变参加 n-1 个固定参数
	 */
	constexpr static SInt arity = sizeof...(TArguments);

	constexpr BasicFunctor() noexcept = default;
};

} // namespace Functional
} // namespace BR
