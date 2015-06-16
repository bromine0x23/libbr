#pragma once

namespace BR {
namespace Assert {

template< typename T >
inline void type_is_complete() {
	using Helper = char[sizeof(T) ? 1 : -1];
	(void) sizeof(Helper);
}

} // namespace Assert
} // namespace BR