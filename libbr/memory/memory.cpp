#include <libbr/memory/bad_weak_pointer.hpp>
#include <libbr/memory/memory_compare.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/memory/memory_move.hpp>
#include <libbr/memory/memory_set.hpp>
#include <cstring>

namespace BR {

BadWeakPointer::~BadWeakPointer() noexcept {
}

auto memory_compare(void const * X, void const * Y, Size n) -> Relation {
	return to_relation(std::memcmp(X, Y, n));
}

auto BadWeakPointer::what() const noexcept -> Message {
	return "BadWeakPointer";
}

void memory_copy(void * D, void const * S, Size n) {
	std::memcpy(D, S, n);
}

void memory_move(void * D, void const * S, Size n) {
	std::memmove(D, S, n);
}

auto memory_search(void const * D, UInt8 b, Size n) -> void const * {
	return memchr(D, b, n);
}

auto memory_search(void * D, UInt8 b, Size n) -> void * {
	return memchr(D, b, n);
}

auto memory_set(void * D, Byte v, Size n) -> void * {
	return std::memset(D, v, n);
}

} // namespace BR