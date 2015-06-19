#pragma once

#include <libbr/config.hpp>
#include <libbr/iterator/reverse_iterator.hpp>

namespace BR {

template< typename TContainer >
inline auto crbegin(TContainer const & container) -> decltype(container.crbegin()) {
	return container.crbegin();
}

} // namespace BR