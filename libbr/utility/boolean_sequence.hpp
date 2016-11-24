/**
 * @file
 * @brief BoolSequence
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integral_sequence.hpp>

namespace BR {

/**
 * @brief 封装布尔常量列表
 */
template< bool... TBn >
using BooleanSequence = IntegerSequence< bool, TBn... >;

} // namespace BR
