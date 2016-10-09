/**
 * @file
 * @brief GB18030编码
 * @author Bromine0x23
 * @since 2016/4/5
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

struct GB18030Encoding {

	using CodeUnit = Char8;

	using CodePoint = UInt32;

	static constexpr auto NAME = "GB18030";

	static constexpr auto MAX_ENCODED_LENGTH = 4;

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

}; // struct UTF8Encoding

} // namespace BR