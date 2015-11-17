/**
 * @file
 * @brief OptionalAccessException
 * @author Bromine0x23
 * @since 2015/11/14
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/logic_exception.hpp>

namespace BR {

class OptionalAccessException : public LogicException {
public:
	OptionalAccessException() : LogicException("Bad optional Access") {
	}

	virtual ~OptionalAccessException() noexcept override;
};

} // namespace BR