/**
 * @file
 * @brief class BadWeakPointer
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/exception.hpp>

namespace BR {
inline namespace Memory {

class BadWeakPointer : public Exception {
public:
	~BadWeakPointer() noexcept override;

	auto what() const noexcept -> Message override;
};

} // namespace Memory
} // namespace BR