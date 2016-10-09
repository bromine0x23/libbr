#pragma once

#include <new>
#include <libbr/config.hpp>

namespace BR {

using BadAllocateException = std::bad_alloc;

using BadArrayNewLengthException = std::bad_array_new_length;

using NewHandler = void(*)();

using NoExceptionTag = std::nothrow_t;

constexpr auto no_exception_tag = NoExceptionTag{};

inline NewHandler get_new_handler() noexcept {
	return std::get_new_handler();
}

inline NewHandler set_new_handler(NewHandler new_handler) noexcept {
	return std::set_new_handler(new_handler);
}

} // namespace BR