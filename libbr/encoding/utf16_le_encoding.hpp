/**
 * @file
 * @brief UTF16-LE
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

struct UTF16LEEncoding {

	using CodeUnit = Char8;

	using CodePoint = UInt32;

	static constexpr auto NAME = "UTF-16LE";

	static constexpr auto MAX_ENCODED_LENGTH = 4;

	static constexpr auto MIN_ENCODED_LENGTH = 2;

	static auto point_to_units(CodePoint code, CodeUnit * out) -> Size;

	static auto units_to_point(CodeUnit const * b, CodeUnit const * e) -> CodePoint;

	static auto length(CodePoint code) -> Size;

	static auto length(CodeUnit const * b) -> Size;

	static auto is_newline(CodePoint code) -> bool;

	static auto is_newline(CodeUnit const * b, CodeUnit const * e) -> bool;

}; // struct UTF16LEEncoding

} // namespace BR