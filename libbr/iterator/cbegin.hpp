#pragma once

#include <libbr/config.hpp>

namespace BR {
namespace Iterator {

template< typename TContainer >
inline auto cbegin(TContainer const & container) -> decltype(container.cbegin()) {
	return container.cbegin();
}

} // namespace Iterator
} // namespace BR