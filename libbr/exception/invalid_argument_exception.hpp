#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/logical_exception.hpp>

namespace BR {
namespace Exception {

class InvalidArgumentException : public LogicalException {
public:
	using BaseException = LogicalException;

	InvalidArgumentException() noexcept;

	explicit InvalidArgumentException(char const * message) noexcept;

	InvalidArgumentException(InvalidArgumentException const &) noexcept;

	virtual ~InvalidArgumentException() noexcept;

	InvalidArgumentException & operator=(InvalidArgumentException const &) noexcept;
};

} // namespace Exception
} // namespace BR