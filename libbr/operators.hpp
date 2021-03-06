/**
 * @file
 * @brief 运算符模块
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

/**
 * @brief 运算符模块
 */
inline namespace Operators {
} // namespace Operators

} // namespace BR

#include <libbr/operators/decrementable.hpp>
#include <libbr/operators/equivalent.hpp>
#include <libbr/operators/generically_equivalent.hpp>
#include <libbr/operators/generically_partially_ordered.hpp>
#include <libbr/operators/generically_totally_ordered.hpp>
#include <libbr/operators/incrementable.hpp>
#include <libbr/operators/partially_ordered.hpp>
#include <libbr/operators/totally_ordered.hpp>