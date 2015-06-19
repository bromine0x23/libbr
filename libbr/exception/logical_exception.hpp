#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/runtime_exception.hpp>

namespace BR {

class LogicalException : public RuntimeException {
public:
	using BaseException = RuntimeException;

	LogicalException() noexcept;

	explicit LogicalException(char const * message) noexcept;

	LogicalException(LogicalException const &) noexcept;

	virtual ~LogicalException() noexcept;

	LogicalException & operator=(LogicalException const &) noexcept;
};

} // namespace BR