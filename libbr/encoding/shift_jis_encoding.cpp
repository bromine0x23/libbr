#include <libbr/encoding/shift_jis_encoding.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/encoding/invalid_code_point_exception.hpp>
#include <libbr/type_traits/make_unsigned.hpp>


namespace BR {

namespace {

static const UInt8 LENGTH[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1
};

} // namespace [anonymous]

auto ShiftJISEncoding::point_to_units(CodePoint code, CodeUnit * out) -> Size {
	CodeUnit * p = out;
	if ((code & 0xFF00U) != 0) {
		*p++ = CodeUnit((code >>  8) & 0xFF);
	}
	*p++ = CodeUnit(code & 0xFF);
	return p - out;
}

auto ShiftJISEncoding::units_to_point(CodeUnit const * b, CodeUnit const * e) -> CodePoint {
	auto l = length(b);
	auto code = MakeUnsigned<CodeUnit>(*b++);
	if (l == 1) {
		return code;
	}
	for (Size i = 1; i < l; ++i) {
		if (b >= e) {
			break;
		}
		code = CodePoint((code << 8) + MakeUnsigned<CodeUnit>(*b++));
	}
	return code;
}

auto ShiftJISEncoding::length(CodePoint code) -> Size {
	if (code < 0x100U) {
		return LENGTH[code] == 1 ? 1 : 0;
	} else if (code <= 0xFFFFU) {
		return 2;
	} else {
		throw InvalidCodePointException<CodePoint>(NAME, code);
	}
}

auto ShiftJISEncoding::length(CodeUnit const * b) -> Size {
	return Size(LENGTH[MakeUnsigned<CodeUnit>(*b)]);
}

} // namespace BR
