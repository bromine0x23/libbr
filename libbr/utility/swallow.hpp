/**
 * @file
 * @brief
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

template< typename ... T >
inline void swallow(T &&...) noexcept {
}

} // namespace BR
