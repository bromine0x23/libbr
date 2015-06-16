#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/exception.hpp>

namespace BR {
namespace Exception {

class RuntimeException : public Exception {
public:
	using BaseException = Exception;

	RuntimeException() noexcept;

	explicit RuntimeException(char const * message) noexcept;

	RuntimeException(RuntimeException const & exception) noexcept;

	virtual ~RuntimeException() noexcept;

	RuntimeException & operator=(RuntimeException const & exception) noexcept;
};

} // namespace Exception
} // namespace BR