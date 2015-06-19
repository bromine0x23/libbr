#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/reverse_iterator.hpp>

namespace BR {

template< typename TContainer >
inline auto crend(TContainer const & container) -> decltype(container.crend()) {
	return container.crend();
}

} // namespace BR