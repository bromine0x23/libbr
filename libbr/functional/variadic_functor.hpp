/**
 * @file
 * @brief 变参函数对象基类
 * @author Bromine0x23
 * @since 2016/11/21
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/basic_functor.hpp>

namespace BR {

inline namespace Functional {

/**
 * @brief 变参函数对象基类
 */
struct VariadicFunctor : public BasicFunctor<> {
	/**
	 * @brief 元数
	 */
	constexpr static SInt arity = -1;

	constexpr VariadicFunctor() noexcept = default;
};

} // namespace Functional

} // namespace BR
