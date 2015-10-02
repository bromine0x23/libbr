#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/logic_exception.hpp>

namespace BR {

class IndexOutOfRangeException : public LogicException {
public:
	using BaseException = LogicException;

	IndexOutOfRangeException() : BaseException("BR::IndexOutOfRangeException") {};

	explicit IndexOutOfRangeException(std::string const & message) : BaseException(message) {};

	explicit IndexOutOfRangeException(CString<NChar> message) : BaseException(message) {};

	virtual ~IndexOutOfRangeException() noexcept;
};

} // namespace BR