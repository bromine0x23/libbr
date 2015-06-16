#pragma once

#include <libbr/config.hpp>

namespace BR {
namespace Iterator {

template< typename TContainer >
inline auto cend(TContainer const & container) -> decltype(container.cend()) {
	return container.cend();
}

} // namespace Iterator
} // namespace BR