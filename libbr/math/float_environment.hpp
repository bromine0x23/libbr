/**
 * @file
 * @brief float environment
 * @author Bromine0x23
 * @date 2016/11/14
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/argument_exception.hpp>

namespace BR {
inline namespace Math {
namespace Floating {

/**
 * @brief Environment, like std::fenv_t
 */
struct Environment;

/**
 * @brief RoundMode
 */
enum class RoundMode : UInt;

constexpr auto to_i(RoundMode mode) noexcept -> UInt {
	return static_cast<UInt>(mode);
}

enum class RoundMode : UInt {
	nearest           = 0x0000,
	negative_infinity = 0x0400,
	positive_infinity = 0x0800,
	zero              = 0x0C00,
};

/**
 * @brief ExceptionType
 */
enum class Exceptions : UInt;

constexpr auto to_i(Floating::Exceptions exceptions) noexcept -> UInt {
	return static_cast<UInt>(exceptions);
}

constexpr auto operator|(Exceptions x, Exceptions y) noexcept -> Exceptions {
	return Exceptions(to_i(x) | to_i(y));
}

enum class Exceptions : UInt {
	invalid         = 0x01,
	divided_by_zero = 0x04,
	overflow        = 0x08,
	underflow       = 0x10,
	inexact         = 0x20,
	all             = invalid | divided_by_zero | overflow | underflow | inexact
};

constexpr auto operator&(Exceptions x, Exceptions y) noexcept -> bool {
	return (to_i(x) & to_i(y) & to_i(Exceptions::all)) != 0;
}

/**
 * @brief BadRoundModeException
 */
class BadRoundModeException : public ArgumentException {
public:
	explicit BadRoundModeException(RoundMode mode) : ArgumentException("BR::BadRoundModeException"), mode(mode) {
	}

	~BadRoundModeException() noexcept override {
	}

	RoundMode const mode;
}; // class BadRoundModeException

/**
 * @brief BadEnvironmentException
 */
class BadEnvironmentException : public ArgumentException {
public:
	explicit BadEnvironmentException(Environment const & environment) : ArgumentException("BR::BadEnvironmentException"), environment(environment) {
	}

	~BadEnvironmentException() noexcept override {
	}

	Environment const & environment;
}; // class BadEnvironmentException

/**
 * @brief BadExceptionException
 */
class BadExceptionsException : public ArgumentException {
public:
	explicit BadExceptionsException(Exceptions exceptions) : ArgumentException("BR::BadExceptionException"), exceptions(exceptions) {
	}

	~BadExceptionsException() noexcept override {
	}

	Exceptions exceptions;
}; // class BadEnvironmentException

} // namespace Floating
} // inline namespace Math
} // namespace BR

extern "C" {

/**
 * @brief like std::fegetround
 * @return round mode
 */
auto libbr_get_floating_round_mode() -> BR::Floating::RoundMode;

/**
 * @brief like std::fesetround
 * @param[in] mode new round mode
 * @return true on success
 */
auto libbr_set_floating_round_mode(BR::Floating::RoundMode mode) -> bool;

/**
 * @brief like std::fegetenv
 * @param[out] environment
 */
void libbr_get_floating_environment(BR::Floating::Environment & environment);

/**
 * @brief like std::fesetenv
 * @param[in] environment new environment
 * @return true on success
 */
auto libbr_set_floating_environment(BR::Floating::Environment const & environment) -> bool;

void libbr_set_default_floating_environment();


auto libbr_get_floating_exceptions() -> BR::Floating::Exceptions;

auto libbr_test_floating_exceptions(BR::Floating::Exceptions exceptions) -> bool;

auto libbr_throw_floating_exceptions(BR::Floating::Exceptions exceptions) -> bool;

auto libbr_clear_floating_exceptions(BR::Floating::Exceptions exceptions) -> bool;

}

#if defined(BR_GCC) || defined(BR_CLANG)

namespace BR {
inline namespace Math {
namespace Floating {

struct Environment {
	UInt16 control_word;
	UInt16 _unused0;
	UInt16 status_word;
	UInt16 _unused1;
	UInt16 tag_word;
	UInt16 _unused2;
	UInt32 instruction_pointer_offset;
	UInt16 instruction_pointer_selector;
	UInt16 operand:11;
	UInt16 _unused3:5;
	UInt32 data_offset;
	UInt16 data_selector;
	UInt16 _unused4;
};

static_assert(sizeof(Environment) == 28);

} // namespace Floating
} // inline namespace Math
} // namespace BR

#else

#include <cfenv>

namespace BR {
inline namespace Math {
inline namespace Floating {

struct Environment : public std::fenv_t {};

} // inline namespace Floating
} // inline namespace Math
} // namespace BR

#endif

namespace BR {
inline namespace Math {
namespace Floating {

inline auto get_round_mode() -> RoundMode {
	return libbr_get_floating_round_mode();
}

inline void set_round_mode(RoundMode mode) noexcept(false) {
	if (!libbr_set_floating_round_mode(mode)) {
		throw BadRoundModeException(mode);
	}
}

inline void get_environment(Environment & environment) {
	libbr_get_floating_environment(environment);
}

inline void set_environment(Environment const & environment) noexcept(false) {
	if (!libbr_set_floating_environment(environment)) {
		throw BadEnvironmentException(environment);
	}
}

inline void set_default_environment() {
	libbr_set_default_floating_environment();
}

inline auto get_exceptions() -> Exceptions {
	return libbr_get_floating_exceptions();
}

inline auto test_exceptions(Exceptions exceptions) -> bool {
	return libbr_test_floating_exceptions(exceptions);
}

inline void throw_exceptions(Exceptions exceptions) noexcept(false) {
	if (!libbr_throw_floating_exceptions(exceptions)) {
		throw BadExceptionsException(exceptions);
	}
}

inline void clear_exceptions(Exceptions exceptions) noexcept(false) {
	if (!libbr_clear_floating_exceptions(exceptions)) {
		throw BadExceptionsException(exceptions);
	}
}

} // namespace Floating
} // inline namespace Math
} // namespace BR