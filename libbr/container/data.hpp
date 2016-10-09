/**
 * @file
 * @brief data
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename T, Size S >
constexpr auto data(CArray< T, S > const & array) noexcept -> T * {
	return array;
}

template< typename TContainer >
BR_CONSTEXPR_AFTER_CXX11 auto data(TContainer & container) -> decltype(container.data()) {
	return container.data();
}

template< typename TContainer >
BR_CONSTEXPR_AFTER_CXX11 auto data(TContainer const & container) -> decltype(container.data()) {
	return container.data();
}

} // namespace BR