#include <libbr/encoding/utf8_encoding.hpp>
#include <libbr/encoding/invalid_code_point_exception.hpp>
#include <libbr/type_operate/make_unsigned.hpp>

namespace BR {

namespace {

UInt8 const LENGTH[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 1, 1
};

} // namespace [anonymous]

auto UTF8Encoding::point_to_units(CodePoint code, CodeUnit * out) -> Size {
	static auto trails = [](CodePoint c, int shift) -> CodeUnit {
		return CodeUnit(((c >> shift) & 0x3F) | 0x80);
	};
	CodeUnit * p = out;
	if ((code & 0xFFFFFF80) == 0) {
		*p++ = MakeUnsigned<CodeUnit>(code);
	} else {
		if ((code & 0xFFFFF800) == 0) {
			*p++ = CodeUnit(((code >> 6) & 0x1F) | 0xc0);
		} else if ((code & 0xFFFF0000) == 0) {
			*p++ = CodeUnit(((code >> 12) & 0x0F) | 0xE0);
			*p++ = trails(code, 6);
		} else if ((code & 0xFFE00000) == 0) {
			*p++ = CodeUnit(((code >> 18) & 0x07) | 0xF0);
			*p++ = trails(code, 12);
			*p++ = trails(code,  6);
		} else if ((code & 0xFC000000) == 0) {
			*p++ = CodeUnit(((code >> 24) & 0x03) | 0xF8);
			*p++ = trails(code, 18);
			*p++ = trails(code, 12);
			*p++ = trails(code,  6);
		} else if ((code & 0x80000000) == 0) {
			*p++ = CodeUnit(((code >> 30) & 0x01) | 0xFC);
			*p++ = trails(code, 24);
			*p++ = trails(code, 18);
			*p++ = trails(code, 12);
			*p++ = trails(code,  6);
		} else if (code == 0xFFFFFFFEU) {
			*p++ = CodeUnit(0xFE);
		} else if (code == 0xFFFFFFFFU) {
			*p++ = CodeUnit(0xFF);
		} else {
			throw InvalidCodePointException<CodePoint>(NAME, code);
		}
		*p++ = CodeUnit((code & 0x3F) | 0x80);
	}
	return Size(p - out);
}

auto UTF8Encoding::units_to_point(CodeUnit const * b, CodeUnit const * /*e*/) -> CodePoint {
	Size l(length(b));
	auto code = MakeUnsigned<CodeUnit>(*b++);
	if (l > 1) {
		--l;
		code &= (1 << (6 - l)) - 1;
		for (; l--;) {
			code = (code << 6) | ((*b++) & ((1 << 6) - 1));
		}
	} else {
		if (code > 0xFDU) {
			code = code == 0xFE ? 0xFFFFFFFEU : 0xFFFFFFFFU;
		}
	}
	return code;
}

auto UTF8Encoding::length(CodePoint code) -> Size {
	if      ((code & 0xFFFFFF80U) == 0) { return Size(1); }
	else if ((code & 0xFFFFF800U) == 0) { return Size(2); }
	else if ((code & 0xFFFF0000U) == 0) { return Size(3); }
	else if ((code & 0xFFE00000U) == 0) { return Size(4); }
	else if ((code & 0xFC000000U) == 0) { return Size(5); }
	else if ((code & 0x80000000U) == 0) { return Size(6); }
	else if (code == 0xFFFFFFFEU) { return Size(1); }
	else if (code == 0xFFFFFFFFU) { return Size(1); }
	else {
		throw InvalidCodePointException<CodePoint>(NAME, code);
	}
}

auto UTF8Encoding::length(CodeUnit const * b) -> Size {
	return Size(LENGTH[MakeUnsigned<CodeUnit>(*b)]);
}

auto UTF8Encoding::is_newline(CodePoint code) -> bool {
	return code == 0x000D || code == 0x0085 || code == 0x2028 || code == 0x2029;
}

auto UTF8Encoding::is_newline(CodeUnit const * b, CodeUnit const * e) -> bool {
	if (b < e) {
		if (*b == 0x0A) {
			return true; // '\n'
		}
		if (b + 1 < e) {
			if (b[1] == 0x85 && b[0] == 0xC2) {
				return true; // U+0085
			}
			if (b + 2 < e) {
				if ((b[2] == 0xA8 || b[2] == 0xA9) && b[1] == 0x80 && b[0] == 0xE2) {
					return true; // U+2028, U+2029
				}
			}
		}
	}
	return false;
}

} // namespace BR