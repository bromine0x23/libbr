/**
 * @file
 * @brief BoolSequence
 * @author Bromine0x23
 * @since 2015/11/1
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/integer_sequence.hpp>

namespace BR {

/**
 * @brief 封装布尔常量列表
 */
template< bool... TBn >
using BooleanSequence = IntegerSequence< bool, TBn... >;

} // namespace BR
