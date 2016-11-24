/**
 * @file
 * @brief LengthException
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/logic_exception.hpp>

namespace BR {

class LengthException : public LogicException {
public:
	using BaseException = LogicException;

	LengthException() : BaseException("BR::LengthException") {
	}

	explicit LengthException(RawString<NChar> const & message) : BaseException(message) {
	}

	explicit LengthException(CString<NChar> message) : BaseException(message) {
	}

	~LengthException() noexcept override;
};

} // namespace BR