/**
 * @file
 * @brief size
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename T, Size S >
constexpr auto size(CArray< T, S > const & array) noexcept -> Size {
	return S;
}

template< typename TContainer >
BR_CONSTEXPR_AFTER_CXX11 auto size(TContainer const & container) -> decltype(container.size()) {
	return container.size();
}

} // namespace BR