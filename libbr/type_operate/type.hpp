/**
 * @file
 * @brief 类型包装
 * @author Bromine0x23
 * @since 2015/6/16
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

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

/**
 * @brief 包装类型列表
 * @tparam T 被包装类型
 */
template< typename ... T >
struct Types {};

} // namespace BR