/**
 * @file
 * @brief OptionalAccessException
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/logic_exception.hpp>

namespace BR {
namespace Container {

/**
 * @brief Exception indicating checked access to an optional that doesn't contain a value.
 */
class OptionalAccessException : public LogicException {
public:
	/**
	 * @brief Constructs the exception object.
	 */
	OptionalAccessException() : LogicException("Bad optional Access") {
	}

	/**
	 * @brief Destructs the exception object.
	 */
	virtual ~OptionalAccessException() noexcept override;
};

} // namespace Container
} // namespace BR