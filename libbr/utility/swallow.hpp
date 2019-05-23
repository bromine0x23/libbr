/**
 * @file
 * @brief 接收任意参数的空函数
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

/**
 * @brief 接收任意参数的空函数
 * @tparam T 参数类型
 */
template< typename ... T >
constexpr inline void swallow(T &&...) noexcept {
}

} // namespace BR
