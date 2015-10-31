#include <libbr/assert/assert.hpp>
#include <libbr/memory/allocator_argument_tag.hpp>
#include <libbr/memory/bad_weak_pointer.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/memory/memory_move.hpp>

namespace BR {

BadWeakPointer::~BadWeakPointer() noexcept {
}

auto BadWeakPointer::what() const noexcept -> Message {
	return "BadWeakPointer";
}

void memory_copy(void const * S, Size n, void * D) {
	auto s = static_cast< Byte const * >(S);
	auto d = static_cast< Byte * >(D);
	for (auto l = n; 0 < l; --l) {
		*d++ = *s++;
	}
}

void memory_move(void const * S, Size n, void * D) {
	auto s = static_cast< Byte const * >(S);
	auto d = static_cast< Byte * >(D);
	if (d - s < PointerDifference(n)) {
		s += n;
		d += n;
		for (auto l = n; 0 < l; --l) {
			*d-- = *s--;
		}
	} else {
		memory_copy(S, n, D);
	}
}

auto memory_set(void * D, Size n, Byte v) -> void * {
	auto d = static_cast< Byte * >(D);
	// TODO: OPT
	for (; n > 0; --n) {
		*d++ = v;
	}
	return D;
}

} // namespace BR