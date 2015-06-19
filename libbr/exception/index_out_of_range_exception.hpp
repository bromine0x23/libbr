#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/logical_exception.hpp>

namespace BR {

class IndexOutOfRangeException : public LogicalException {
public:
	using BaseException = LogicalException;

	IndexOutOfRangeException() noexcept;

	explicit IndexOutOfRangeException(char const * message) noexcept;

	IndexOutOfRangeException(IndexOutOfRangeException const &) noexcept;

	virtual ~IndexOutOfRangeException() noexcept;

	IndexOutOfRangeException & operator=(IndexOutOfRangeException const &) noexcept;
};

} // namespace BR