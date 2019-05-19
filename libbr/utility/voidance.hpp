/**
 * @file
 * @brief Voidance
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/type_transform/remove_reference.hpp>
#include <libbr/utility/conditional.hpp>
#include <libbr/utility/conjunction.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 将任意类型序列映射至 void
 * @author Bromine0x23
 */
template< typename ... >
using Voidance = void;

} // namespace Utility

} // namespace BR
