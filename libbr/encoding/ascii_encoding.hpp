/**
 * @file
 * @brief ASCII编码
 * @author Bromine0x23
 * @since 16/4/5
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/encoding/invalid_code_point_exception.hpp>

namespace BR {

struct ASCIIEncoding {

	using CodeUnit = Char8;

	using CodePoint = UInt8;

	static constexpr auto NAME = "ASCII";

	static constexpr auto MAX_ENCODED_LENGTH = 1;

	static constexpr auto MIN_ENCODED_LENGTH = 1;

	static auto point_to_units(CodePoint code, CodeUnit * out) -> Size {
		*out = CodeUnit(code & 0xFF);
		return Size(1);
	}

	static constexpr auto units_to_point(CodeUnit const * b, CodeUnit const * /*e*/) -> CodePoint {
		return CodePoint(*b);
	}

	/**
	 * @param point 码位
	 * @return 码位译成码元序列后的长度
	 */
	static constexpr auto length(CodePoint point) -> Size {
		return Size(1);
	}

	/**
	 *
	 * @param b 码元序列
	 * @return 码元序列首个码位所占的长度
	 */
	static constexpr auto length(CodeUnit const * b) -> Size {
		return Size(1);
	}

	static constexpr auto is_newline(CodePoint code) -> bool {
		return code == 0x0A; // '\n'
	}

	static constexpr auto is_newline(CodeUnit const * b, CodeUnit const * e) -> bool {
		return b < e && *b == 0x0A; // '\n'
	}

}; // struct UTF8Encoding

} // namespace BR