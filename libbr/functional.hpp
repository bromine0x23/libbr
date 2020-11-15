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

#include <libbr/functional/equal.hpp>
#include <libbr/functional/greater.hpp>
#include <libbr/functional/greater_equal.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/functional/less_equal.hpp>

#include <libbr/functional/plus.hpp>
#include <libbr/functional/minus.hpp>
#include <libbr/functional/multiply.hpp>
#include <libbr/functional/divide.hpp>
#include <libbr/functional/modulo.hpp>
#include <libbr/functional/unary_plus.hpp>
#include <libbr/functional/unary_minus.hpp>

#include <libbr/functional/logical_and.hpp>
#include <libbr/functional/logical_or.hpp>
#include <libbr/functional/logical_not.hpp>

#include <libbr/functional/bit_and.hpp>
#include <libbr/functional/bit_or.hpp>
#include <libbr/functional/bit_xor.hpp>
#include <libbr/functional/bit_not.hpp>
#include <libbr/functional/bit_lshift.hpp>
#include <libbr/functional/bit_rshift.hpp>