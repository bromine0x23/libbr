/**
 * @file
 * @brief class BadWeakPointer
 * @author Bromine0x23
 * @since 2015/10/26
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/exception.hpp>

namespace BR {

class BadWeakPointer : public Exception {
public:
	~BadWeakPointer() noexcept override;

	auto what() const noexcept -> Message override;
};

} // namespace BR