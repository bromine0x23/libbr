#include <libbr/memory/memory_compare.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/memory/memory_move.hpp>
#include <libbr/memory/memory_search.hpp>
#include <libbr/memory/memory_set.hpp>
#include <cstring>

auto libbr_memory_compare(void const * X, void const * Y, BR::Size n) -> BR::Relation {
	return BR::to_relation(std::memcmp(X, Y, n));
}

void libbr_memory_copy(void * D, void const * S, BR::Size n) {
	std::memcpy(D, S, n);
}

void libbr_memory_move(void * D, void const * S, BR::Size n) {
	std::memmove(D, S, n);
}

auto libbr_memory_search(void * D, BR::UInt8 b, BR::Size n) -> void * {
	return memchr(D, b, n);
}

auto libbr_memory_set(void * D, BR::Byte v, BR::Size n) -> void * {
	return std::memset(D, v, n);
}