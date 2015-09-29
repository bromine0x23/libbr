#pragma once

#include <new>
#include <libbr/config.hpp>

namespace BR {

namespace Detail {

inline void * allocate(Size size) {
	return ::operator new(size);
}

inline void deallocate(void * pointer) {
	::operator delete(pointer);
}

} // namespace Detail

using BadAllocateException = std::bad_alloc;

using NewHandler = std::new_handler;

using NothrowTag = std::nothrow_t;

extern NothrowTag nothrow_tag;

/* TODO
inline NewHandler get_new_handler() noexcept {
	return std::get_new_handler();
}
*/

inline NewHandler set_new_handler(NewHandler new_handler) noexcept {
	return std::set_new_handler(new_handler);
}

} // namespace BR