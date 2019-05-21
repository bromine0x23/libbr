/**
 * @file
 * @brief 仿函数模块
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

/**
 * @brief 仿函数模块
 */
inline namespace Functional {
} // namespace Functional

} // namespace BR

#include <libbr/functional/basic_functor.hpp>
#include <libbr/functional/unary_functor.hpp>
#include <libbr/functional/binary_functor.hpp>
#include <libbr/functional/variadic_functor.hpp>

#include <libbr/functional/less.hpp>
#include <libbr/functional/less_equal.hpp>