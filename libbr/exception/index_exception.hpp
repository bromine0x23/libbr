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

class IndexException : public LogicException {
public:
	using BaseException = LogicException;

	IndexException() : BaseException("BR::IndexException") {
	}

	explicit IndexException(RawString<NChar> const & message) : BaseException(message) {
	}

	explicit IndexException(CString<NChar> message) : BaseException(message) {
	}

	~IndexException() noexcept override;
};

} // namespace BR