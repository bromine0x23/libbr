#include <libbr/utility/timer.hpp>

#if defined(BR_LINUX)

#elif defined(BR_WIN32)

#include <windows.h>

#else

#endif // defined

namespace BR {

#if defined(BR_LINUX)

#include <linux/timer.h>

namespace {

} // namespace [anonymous]

#elif defined(BR_WIN32)

namespace {

static Timer::Unit unit = []() {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return static_cast< Timer::Unit >(frequency.QuadPart);
}();

Timer::Unit get_time() noexcept {
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	return static_cast< Timer::Unit >(counter.QuadPart);
}

Timer::Unit quantify(Timer::Unit time) noexcept {
	return time * 1000000000 / unit;
}

} // namespace [anonymous]

#elif defined(BR_LINUX)

#else
#  error "not implement Timer"
#endif // defined

void Timer::start() noexcept {
	run_ = true;
	time_ = get_time();
}

void Timer::stop() noexcept {
	if (is_timing()) {
		run_ = false;
		time_ = get_time() - time_;
	}
}

Timer::Unit Timer::elapsed() const noexcept {
	if (is_timing()) {
		return quantify(get_time() - time_);
	} else {
		return quantify(time_);
	}
}

void Timer::resume() noexcept {
	if (!is_timing()) {
		Unit current = time_;
		start();
		time_ -= current;
	}
}

} // namespace BR
