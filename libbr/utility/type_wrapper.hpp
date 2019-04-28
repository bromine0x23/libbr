/**
 * @file
 * @brief TypeWrapper - 类型包装器
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 类型包装器
 * @tparam T 被包装类型
 */
template< typename T >
struct TypeWrapper {
	/**
	 * @brief 被包装类型
	 */
	using Type = T;

	constexpr TypeWrapper() noexcept = default;
};

/**
 * @brief 类型解包
 * @tparam TWrapper 包装器
 */
template< typename TWrapper >
using TypeUnwrap = typename TWrapper::Type;

/**
 * @brief 类型重包装
 * @tparam TWrapper 包装器
 */
template< typename TWrapper >
using TypeRewrap = TypeWrapper< TypeUnwrap<TWrapper> >;

} // namespace Utility

} // namespace BR