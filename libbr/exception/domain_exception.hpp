/**
 * @file
 * @brief IndexException
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/logic_exception.hpp>

namespace BR {

class DomainException : public LogicException {
public:
	using BaseException = LogicException;

	DomainException() : BaseException("BR::DomainException") {
	}

	explicit DomainException(RawString<NChar> const & message) : BaseException(message) {
	}

	explicit DomainException(CString<NChar> message) : BaseException(message) {
	}

	~DomainException() noexcept override;
};

} // namespace BR