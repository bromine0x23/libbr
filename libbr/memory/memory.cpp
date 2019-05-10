#include <libbr/memory/memory_copy.hpp>
#include <libbr/memory/memory_copy_unsafely.hpp>
#include <libbr/memory/memory_fill.hpp>

#include <cstring>

using namespace BR;

void libbr_memory_copy(void const * source, void * destination, BR::Size count) {
	std::memmove(destination, source, count);
}

void libbr_memory_copy_unsafely(void const * source, void * destination, BR::Size count) {
	std::memcpy(destination, source, count);
}

auto libbr_memory_fill(void * destination, Size count, Byte byte) -> void * {
	return std::memset(destination, byte, count);
}