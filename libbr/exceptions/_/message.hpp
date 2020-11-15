#pragma once

namespace BR {
namespace _ {
namespace Exceptions {

class Message {

private:
	CString<NChar> _string;

public:
	explicit Message(CString<NChar> string);

	Message(Message const & message) noexcept;

	Message & operator=(Message const & message) noexcept;

	~Message();

	auto data() const noexcept -> CString<NChar> {
		return _string;
	}
}; // class Message

} // namespace Exceptions
} // namespace _
} // namespace BR