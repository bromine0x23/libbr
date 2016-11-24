/**
 * @file
 * @brief empty
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename T, Size S >
constexpr auto empty(CArray< T, S > const & array) noexcept -> bool {
	return false;
}

template< typename TContainer >
BR_CONSTEXPR_AFTER_CXX11 auto empty(TContainer const & container) -> decltype(container.empty()) {
	return container.empty();
}

} // namespace BR