/**
 * @file
 * @brief get_temporary_buffer
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/min.hpp>
#include <libbr/container/pair.hpp>

namespace BR {

template< typename TElement >
auto get_temporary_buffer(PointerDifference n) noexcept -> Pair< TElement *, PointerDifference > {
	Pair< TElement *, PointerDifference > r(nullptr, 0);
	PointerDifference const limit = (~PointerDifference(0) ^ PointerDifference(PointerDifference(1) << (sizeof(PointerDifference) * BIT_PER_CHAR - 1))) / sizeof(TElement);
	for (n = min(n, limit); n > 0;) {
		r.first = static_cast< TElement * >(::operator new(n * sizeof(TElement), nothrow_tag));
		if (r.first != nullptr) {
			r.second = n;
			break;
		}
		n /= 2;
	}
	return r;
}

} // namespace BR