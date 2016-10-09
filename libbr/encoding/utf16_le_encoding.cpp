#include <libbr/encoding/utf16_le_encoding.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/string/invalid_code_point_exception.hpp>

namespace BR {

namespace {

UInt8 const LENGTH[] = {
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
};

} // namespace [anonymous]

auto UTF16LEEncoding::point_to_units(CodePoint code, CodeUnit * out) -> Size {
	CodeUnit * p = out;
	if (code < 0x0000FFFFU) {
		*p++ = CodeUnit(code & 0xFFU);
		*p++ = CodeUnit((code & 0xFF00U) >> 8);
	} else if (code < 0x0010FFFFU) {
		UInt16 lead = UInt16(code >> 16) - 1U;
		UInt16 trail_high = UInt16(code & 0xFF00U) >> 8;
		*p++ = CodeUnit(((lead & 0x03U) << 6) + (trail_high >> 2));
		*p++ = CodeUnit((lead >> 2) + 0xD8U);
		*p++ = CodeUnit(code & 0xFFU);
		*p++ = CodeUnit((trail_high & 0x03U) + 0xDCU);
	} else {
		throw InvalidCodePointException<CodePoint>(NAME, code);
	}
	return p - out;
}

auto UTF16LEEncoding::units_to_point(CodeUnit const * b, CodeUnit const * e) -> CodePoint {
	CodeUnit u0 = b[0], u1 = b[1];
	CodePoint code;
	if ((u1 & 0xFCU) == 0xD8U) {
		BR_ASSERT(b + 3 < e);
		BR_ASSERT((b[3] & 0xFCU) == 0xDCU);
		code = ((((u1 - 0xD8U) << 2) + ((u0  & 0xC0U) >> 6) + 1) << 16) + ((((u0 & 0x3FU) << 2) + (b[3] - 0xDCU)) << 8) + b[2];
	} else {
		code = (u1 << 8) + u0;
	}
	return code;
}

auto UTF16LEEncoding::length(CodePoint code) -> Size {
	return Size(code > 0x0000FFFFU ? 4 : 2);
}

auto UTF16LEEncoding::length(CodeUnit const * b) -> Size {
	return Size(LENGTH[b[1]]);
}

auto UTF16LEEncoding::is_newline(CodePoint code) -> bool {
	return code == 0x000DU || code == 0x0085U || code == 0x2028U || code == 0x2029U;
}

auto UTF16LEEncoding::is_newline(CodeUnit const * b, CodeUnit const * e) -> bool {
	if (b + 1 < e) {
		if (b[0] == 0x0A && b[1] == 0x00) {
			return true; // '\n'
		}
		if (b[0] == 0x85 && b[1] == 0x00) {
			return true; // U+0085
		}
		if (b[1] == 0x20 && (b[0] == 0x29 || b[0] == 0x28)) {
			return true; // U+2028, U+2029
		}
	}
	return false;
}

} // namespace BR