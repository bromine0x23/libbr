#include <libbr/assert/assert.hpp>
#include <libbr/exceptions/stl.hpp>
#include <libbr/exceptions/exception.hpp>
#include <libbr/exceptions/runtime_exception.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/strings/string_length.hpp>
#include <libbr/utility/transfer.hpp>

#include <atomic>

namespace BR {

namespace _ {
namespace Exceptions {

struct Representation {
	Size length;
	Size capacity;
	std::atomic<SInt> count;
};

inline auto representation_from_data(NChar const * data) noexcept -> Representation * {
	return reinterpret_cast<Representation *>(const_cast<NChar *>(data) - sizeof(Representation));
}

inline auto data_from_representation(Representation * representation) noexcept -> NChar * {
	return reinterpret_cast<NChar *>(representation) + sizeof(*representation);
}

Message::Message(CString<NChar> string) {
	auto length = string_length(string);
	auto representation = static_cast<Representation *>(::operator new(sizeof(Representation) + length + 1));
	representation->length = length;
	representation->capacity = length;
	representation->count = 0;

	auto data = data_from_representation(representation);

	memory_copy(string, data, length + 1);

	_string = data;
}

inline Message::Message(Message const & message) noexcept : _string(message._string) {
	++(representation_from_data(_string)->count);
}

inline auto Message::operator=(Message const& message) noexcept -> Message & {
	auto old_representation = representation_from_data(_string);
	_string = message._string;
	++(representation_from_data(_string)->count);
	if (--(old_representation->count) < 0) {
		::operator delete(old_representation);
	}
	return *this;
}

inline Message::~Message() {
	auto * representation = representation_from_data(_string);
	if (--(representation->count) < 0) {
		::operator delete(representation);
	}
}

} // namespace Exceptions
} // namespace _

inline namespace Exceptions {

Exception::~Exception() noexcept {
}

auto Exception::what() const noexcept -> CString<NChar> {
	return "BR::Exceptions::Exception";
}

RuntimeException::RuntimeException(RuntimeException const & exception) noexcept : _message(exception._message) {
}

RuntimeException::RuntimeException(CString<NChar> message) : _message(message) {}

RuntimeException::~RuntimeException() noexcept {
}

auto RuntimeException::operator=(RuntimeException const & exception) noexcept -> RuntimeException & {
	_message = exception._message;
	return *this;
}

auto RuntimeException::what() const noexcept -> CString<NChar> {
	return _message.data();
}

} // namespace Exceptions

} // namespace BR