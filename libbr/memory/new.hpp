#pragma once

#include <new>
#include <libbr/config.hpp>

namespace BR {

namespace Detail {
namespace Memory {

inline void *allocate(Size size) {
	return ::operator new(size);
}

inline void deallocate(void *pointer) {
	::operator delete(pointer);
}

} // namespace Memory
} // namespace Detail

using BadAllocateException = std::bad_alloc;

using BadArrayNewLengthException = std::bad_array_new_length;

using NewHandler = void(*)();

using NothrowTag = std::nothrow_t;

constexpr auto nothrow_tag = NothrowTag();

inline NewHandler get_new_handler() noexcept {
	return std::get_new_handler();
}

inline NewHandler set_new_handler(NewHandler new_handler) noexcept {
	return std::set_new_handler(new_handler);
}

} // namespace BR