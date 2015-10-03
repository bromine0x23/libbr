#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/logic_exception.hpp>

namespace BR {

class OutOfRangeException : public LogicException {
public:
	using BaseException = LogicException;

	OutOfRangeException() : BaseException("BR::OutOfRangeException") {};

	explicit OutOfRangeException(std::string const & message) : BaseException(message) {};

	explicit OutOfRangeException(CString<NChar> message) : BaseException(message) {};

	virtual ~OutOfRangeException() noexcept;
};

} // namespace BR