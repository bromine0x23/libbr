/**
 * @file
 * @brief declare_value - 在 decltype 得非求值上下文中产生给定类型值
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

namespace _ {
namespace Utility {

template< typename T >
auto declare_value_helper(int) -> T &&;

template< typename T >
auto declare_value_helper(long) -> T;

} // namespace Utility
} // namespace _

inline namespace Utility {

template< typename T >
auto declare_value() noexcept -> decltype(_::Utility::declare_value_helper<T>(0));

} // namespace Utility

} // namespace BR

