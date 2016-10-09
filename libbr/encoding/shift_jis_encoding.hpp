/**
 * @file
 * @brief Shift-JIS编码
 * @author Bromine0x23
 * @since 2016/10/8
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

struct ShiftJISEncoding {

	using CodeUnit = Char8;

	using CodePoint = UInt32;

	static constexpr auto NAME = "Shift-JIS";

	static constexpr auto MAX_ENCODED_LENGTH = 2;

	static constexpr auto MIN_ENCODED_LENGTH = 1;

	static auto point_to_units(CodePoint code, CodeUnit * out) -> Size;

	static auto units_to_point(CodeUnit const * b, CodeUnit const * e) -> CodePoint;

	static auto length(CodePoint code) -> Size;

	static auto length(CodeUnit const * b) -> Size;

	static constexpr auto is_newline(CodePoint code) -> bool {
		return code == 0x0A; // '\n'
	}

	static constexpr auto is_newline(CodeUnit const * b, CodeUnit const * e) -> bool {
		return b < e && *b == 0x0A; // '\n'
	}

}; // struct ShiftJISEncoding

} // namespace BR