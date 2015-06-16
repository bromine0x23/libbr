#pragma once

#include <new>
#include <libbr/config.hpp>

namespace BR {
namespace Memory {

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

/** TODO
inline NewHandler getNewHandler() noexcept {
	return std::get_new_handler();
}
*/

inline NewHandler setNewHandler(NewHandler new_handler) noexcept {
	return std::set_new_handler(new_handler);
}

} // namespace Memory
} // namespace BR