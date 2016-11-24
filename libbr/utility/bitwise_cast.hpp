/**
 * @file
 * @brief 逐位转换
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/min.hpp>
#include <libbr/memory/memory_copy.hpp>

namespace BR {

template< typename TTo, typename TFrom >
BR_FORCE_INLINE auto bitwise_cast(TFrom const & from) noexcept -> TTo {
	struct { TTo to; } value = {};
	memory_copy(&reinterpret_cast< char & >(value.to), &reinterpret_cast< char const & >(from), min(sizeof(TTo), sizeof(TFrom)));
	return value.to;
}

} // namespace BR