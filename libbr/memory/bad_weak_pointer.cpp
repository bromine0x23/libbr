#include <libbr/memory/bad_weak_pointer.hpp>

namespace BR {

BadWeakPointer::~BadWeakPointer() noexcept {
}

auto BadWeakPointer::what() const noexcept -> Message {
	return "BadWeakPointer";
}

} // namespace BR