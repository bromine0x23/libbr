#pragma once

namespace BR {

template< typename T >
inline void assert_type_completeness() {
	using Helper = char[sizeof(T) ? 1 : -1];
	(void) sizeof(Helper);
}

} // namespace BR