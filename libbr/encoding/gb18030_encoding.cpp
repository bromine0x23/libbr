#include <libbr/encoding/gb18030_encoding.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/encoding/invalid_code_point_exception.hpp>

namespace BR {

namespace {

enum : UInt8 {
	C1, /* one-byte char */
	C2, /* one-byte or second of two-byte char */
	C4, /* one-byte or second or fourth of four-byte char */
	CM  /* first of two- or four-byte char or second of two-byte char */
};

UInt8 const GB18030_LENGTH[] = {
	C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,
	C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,
	C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1, C1,
	C4, C4, C4, C4, C4, C4, C4, C4, C4, C4, C1, C1, C1, C1, C1, C1,
	C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,
	C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,
	C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2,
	C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C2, C1,
	C2, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM,
	CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM,
	CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM,
	CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM,
	CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM,
	CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM,
	CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM,
	CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, CM, C1
};

} // namespace [anonymous]

auto GB18030Encoding::point_to_units(CodePoint code, CodeUnit * out) -> Size {
	CodeUnit *p = out;
	if ((code & 0xFF000000U) != 0) {
		*p++ = CodeUnit((code >> 24) & 0xFFU);
	}
	if ((code & 0x00FF0000U) != 0 || p != out) {
		*p++ = CodeUnit((code >> 16) & 0xFFU);
	}
	if ((code & 0x0000FF00U) != 0 || p != out) {
		*p++ = CodeUnit((code >> 8) & 0xFFU);
	}
	*p++ = CodeUnit(code & 0xFFU);
	Size l(p - out);
	if (length(out) != l) {
		throw InvalidCodePointException<CodePoint>(NAME, code);
	}
	return Size(l);
}

auto GB18030Encoding::units_to_point(CodeUnit const * b, CodeUnit const * e) -> CodePoint {
	Size l(length(b));
	CodePoint code = static_cast<CodePoint>(*b++);
	if (l > 1) {
		for (--l; l-- && b < e;) {
			code = (code << 7) + *b++;
		}
	}
	return code;
}

auto GB18030Encoding::length(CodePoint code) -> Size {
	if      ((code & 0xFF000000U) != 0) { return 4; }
	else if ((code & 0x00FF0000U) != 0) { return 3; }
	else if ((code & 0x0000FF00U) != 0) { return 2; }
	else                                { return 1; }
}

auto GB18030Encoding::length(CodeUnit const * b) -> Size {
	if (GB18030_LENGTH[MakeUnsigned<CodeUnit>(*b)] != CM) {
		return Size(1);
	}
	switch (GB18030_LENGTH[MakeUnsigned<CodeUnit>(*++b)]) {
		case C1:
			return Size(1);
		case C2:
			return Size(2);
		case C4:
			return Size(4);
		default:
			BR_ASSERT(false);
			break;
	}
	return 0;
}

} // namespace BR