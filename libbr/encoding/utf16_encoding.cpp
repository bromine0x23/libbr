#include <libbr/encoding/utf16_encoding.hpp>
#include <libbr/encoding/invalid_code_point_exception.hpp>

namespace BR {

auto UTF16Encoding::point_to_units(CodePoint code, CodeUnit * out) -> Size {
	CodeUnit * p = out;
	if (code < 0x0000FFFFU) {
		*p++ = CodeUnit(code & 0xFFFFU);
	} else if (code < 0x0010FFFFU) {
		*p++ = CodeUnit(((code - 0x00010000U) >> 10) + 0xD800U);
		*p++ = CodeUnit((code & 0x000003FFU) + 0xDC00U);
	} else {
		throw InvalidCodePointException<CodePoint>(NAME, code);
	}
	return Size(p - out);
}

auto UTF16Encoding::units_to_point(CodeUnit const * b, CodeUnit const * e) -> CodePoint {
	CodePoint code;
	CodeUnit lead = b[0];
	if ((lead & 0xFC00U) == 0xD800U) {
		code = ((lead - 0xD800U) << 10) | (b[1] - 0xDC00U) | 0x00010000U;
	} else {
		code = lead;
	}
	return code;
}

auto UTF16Encoding::length(CodePoint code) -> Size {
	return Size(code > 0x0000FFFFU ? 2 : 1);
}

auto UTF16Encoding::length(CodeUnit const * b) -> Size {
	return Size((*b & 0xFC00U) == 0xD800U ? 2 : 1);
}

} // namespace BR