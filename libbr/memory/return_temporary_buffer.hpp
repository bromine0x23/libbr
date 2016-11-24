/**
 * @file
 * @brief return_temporary_buffer
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TElement >
inline void return_temporary_buffer(TElement * p) noexcept {
	::operator delete(p);
}

} // namespace BR