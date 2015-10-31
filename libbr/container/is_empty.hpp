/**
 * @file
 * @brief is_empty
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename T, Size S >
constexpr auto is_empty(CArray< T, S > const & array) noexcept -> bool {
	return false;
}

template< typename TContainer >
BR_CONSTEXPR_AFTER_CXX11 auto is_empty(TContainer const & container) -> decltype(container.is_empty()) {
	return container.empty();
}

} // namespace BR