#pragma once

#include <libbr/config.hpp>

namespace BR {

class Timer {
public:
	typedef UInt64 Unit;

public:
	Timer() : run_(false) {}

	bool is_timing() const noexcept {
		return run_;
	}

	void start() noexcept;

	void stop() noexcept;

	Unit elapsed() const noexcept;

	void resume() noexcept;

private:
	bool run_;
	Unit time_;
};

} // namespace BR
