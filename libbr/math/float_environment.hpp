/**
 * @file
 * @brief float environment
 * @author Bromine0x23
 * @date 2016/11/14
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {
inline namespace Math {
inline namespace Environment {

struct FloatEnvironment {
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

static_assert(sizeof(FloatEnvironment) == 28);

enum class FloatRoundMode : SInt {
	to_nearest  = 0x0000,
	toward_zero = 0x0C00,
	downward    = 0x0400,
	upward      = 0x0800,
};

constexpr auto to_i(FloatRoundMode mode) noexcept -> SInt {
	return static_cast<SInt>(mode);
}

enum class FloatException : SInt {
	invalid         = 0x01,
	divided_by_zero = 0x04,
	overflow        = 0x08,
	underflow       = 0x10,
	inexact         = 0x20,
	all             = invalid | divided_by_zero | overflow | underflow | inexact
};

constexpr auto to_i(FloatException exception) noexcept -> SInt {
	return static_cast<SInt>(exception);
}

} // inline namespace Environment
} // inline namespace Math
} // namespace BR

extern "C" {

#if defined(BR_GCC) || defined(BR_CLANG)
inline auto libbr_get_float_round_mode() -> BR::FloatRoundMode {
	BR::SInt control;
	asm("fnstcw %0" : "=m"(control));
	return BR::FloatRoundMode(control & 0xC00);
}

inline auto libbr_set_float_round_mode(BR::FloatRoundMode mode) -> bool {
	if ((BR::to_i(mode) & ~0xC00) != 0) {
		return false;
	}
	BR::SInt control;
	asm("fnstcw %0" : "=m"(control));
	control = (control & ~0xC00) | BR::to_i(mode);
	asm("fldcw %0" : : "m"(control));
	return true;
}

inline auto libbr_get_float_environment(BR::FloatEnvironment & environment) -> bool {
	asm("fnstenv %0" : "=m" (environment));
	asm("fldenv %0" : : "m" (environment));
	return true;
}

inline auto libbr_set_float_environment(BR::FloatEnvironment const & environment) -> bool {
	BR::FloatEnvironment temp;
	asm("fnstenv %0" : "=m" (temp));
	temp.control_word = (temp.control_word & ~(BR::to_i(BR::FloatException::all) | BR::to_i(BR::FloatRoundMode::to_nearest))) | (environment.control_word & (BR::to_i(BR::FloatException::all) | BR::to_i(BR::FloatRoundMode::toward_zero)));
	temp.status_word = (temp.status_word & ~BR::to_i(BR::FloatException::all)) | (environment.status_word & BR::to_i(BR::FloatException::all));
	temp.instruction_pointer_offset = 0;
	temp.instruction_pointer_selector = 0;
	temp.operand = 0;
	temp.data_offset = 0;
	temp.data_selector = 0;
	asm("fldenv %0" : : "m" (temp));
	return true;

}
#elif defined(BR_MSVC)
inline auto libbr_get_float_round_mode() -> BR::FloatRoundMode {
	SInt control;
	__asm { fnstcw control }
	return BR::FloatRoundMode(control & 0xC00);
}

inline auto libbr_set_float_round_mode(BR::FloatRoundMode mode) -> bool {
	if ((BR::to_i(mode) & ~0xC00) != 0) {
		return false;
	}
	int control;
	__asm { fnstcw control }
	control = (control & ~0xC00) | BR::to_i(mode);
	__asm { fldcw control }
	return true;
}

inline auto libbr_get_float_environment(FloatEnvironment & environment) -> bool {
	__asm { fnstenv environment }
	__asm { fldenv environment }
	return true;
}
#else
auto libbr_get_float_round_mode() -> BR::FloatRoundMode;

auto libbr_set_float_round_mode(BR::FloatRoundMode mode) -> bool;
#endif

}

namespace BR {
inline namespace Math {
inline namespace Environment {

inline auto get_float_round_mode() -> FloatRoundMode {
	return libbr_get_float_round_mode();
}

inline auto set_float_round_mode(FloatRoundMode mode) -> bool {
	return libbr_set_float_round_mode(mode);
}

inline auto get_float_environment(FloatEnvironment & environment) -> bool {
	return libbr_get_float_environment(environment);
}

inline auto set_float_environment(FloatEnvironment const & environment) -> bool {
	return libbr_set_float_environment(environment);
}

} // inline namespace Environment
} // inline namespace Math
} // namespace BR