/**
 * @file
 * @brief return_temporary_buffer
 * @author Bromine0x23
 * @since 2015/11/19
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename TElement >
inline void return_temporary_buffer(TElement * p) noexcept {
	::operator delete(p);
}

} // namespace BR