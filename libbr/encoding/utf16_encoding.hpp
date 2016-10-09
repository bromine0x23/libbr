/**
 * @file
 * @brief UTF16
 * @author Bromine0x23
 * @since 2016/4/4
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

struct UTF16Encoding {

	using CodeUnit = Char16;

	using CodePoint = UInt32;

	static constexpr auto NAME = "UTF-16";

	static constexpr auto MAX_ENCODED_LENGTH = 2;

	static constexpr auto MIN_ENCODED_LENGTH = 1;

	static auto point_to_units(CodePoint code, CodeUnit * out) -> Size;

	static auto units_to_point(CodeUnit const * b, CodeUnit const * e) -> CodePoint;

	static auto length(CodePoint code) -> Size;

	static auto length(CodeUnit const * b) -> Size;

}; // struct UTF16Encoding

} // namespace BR