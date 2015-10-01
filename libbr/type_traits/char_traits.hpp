#pragma once

#include <cstdio>
#include <cstring>
#include <cwchar>
#include <libbr/config.hpp>
#include <libbr/assert.hpp>
#include <libbr/math/relation.hpp>

namespace BR {

template< typename TChar >
struct CharTraits {
	using Char = TChar;
	using Int = UInt64;
	// TODO: using Offset = std::streamoff;
	// TODO: using Position = std::streampos;
	// TODO: using State = std::mbstate_t;

	static constexpr bool eq(Char c0, Char c1) noexcept { return c0 == c1; }
	static constexpr bool lt(Char c0, Char c1) noexcept { return c0 <  c1; }
	static constexpr bool eq_int(Int i0, Int i1) noexcept { return i0 == i1; }

	static Size length(CString<Char> s) {
		Size result = 0;
		for (; !eq(*s, Char(0)); ++s) {
			++result;
		}
		return result;
	}

	static Relation compare(CString<Char> s0, CString<Char> s1, Size size) noexcept {
		for (; size > 0; --size, ++s0, ++s1) {
			if (lt(*s0, *s1)) { return Relation::LT; }
			if (lt(*s1, *s0)) { return Relation::GT; }
		}
		return Relation::EQ;
	}

	static Char const * find(Char const * s, Size size, Char const & c) {
		for (; size-- > 0; ++s) {
			if (eq(*s, c)) {
				return s;
			}
		}
		return nullptr;
	}

	static void assign(Char & c0, Char const & c1) noexcept {
		c0 = c1;
	}

	static Char * assign(Char * s, Size size, Char c) {
		Char * result = s;
		for (; size > 0; --size) {
			assign(*s++, c);
		}
		return result;
	}

	static Char * move(Char * s0, CString<Char> s1, Size size) {
		Char * result = s0;
		if (s0 < s1) {
			for (; size > 0; --size) {
				assign(*s0++, *s1++);
			}
		} else if (s1 < s0) {
			s0 += size;
			s1 += size;
			for (; size > 0; --size) {
				assign(*--s0, *--s1);
			}
		}
		return result;
	}

	static Char * copy(Char * s0, CString<Char> s1, Size size) {
		BR_ASSERT(s1 < s0 || s1 >= s0 + size);
		Char * result = s0;
		for (; size > 0; --size) {
			assign(*s0++, *s1++);
		}
		return result;
	}

	static constexpr Char to_char(Int  i) noexcept { return Char(i); }
	static constexpr Int  to_int (Char c) noexcept { return Int (c); }

	static constexpr Int eof() noexcept { return Int(EOF); }

	static constexpr Int not_eof(Int i) noexcept { return eq_int(i, eof()) ? ~eof() : i; }
}; // struct CharTraits<TChar>

template <>
struct CharTraits<NChar> {
	using Char = NChar;
	using Int = UInt32;
	// TODO: using Offset = std::streamoff;
	// TODO: using Position = std::streampos;
	// TODO: using State = std::mbstate_t;

	static constexpr bool eq(Char c0, Char c1) noexcept { return c0 == c1; }
	static constexpr bool lt(Char c0, Char c1) noexcept { return UInt8(c0) < UInt8(c1); }

	static Size length(CString<Char> s) {
		return std::strlen(s);
	}

	static constexpr Relation compare(CString<Char> s0, CString<Char> s1, Size size) noexcept {
		return to_relation(std::memcmp(s0, s1, size));
	}

	static Char const * find(Char const * s, Size size, Char const & c) {
		return reinterpret_cast< Char const * >(std::memchr(s, to_int(c), size));
	}

	static void assign(Char & c0, Char const & c1) noexcept {
		c0 = c1;
	}

	static Char * assign(Char * s, Size size, Char c) {
		return reinterpret_cast< Char * >(std::memset(s, to_int(c), size));
	}

	static Char * move(Char * s0, CString<Char> s1, Size size) {
		return reinterpret_cast< Char * >(std::memmove(s0, s1, size));
	}

	static Char * copy(Char * s0, CString<Char> s1, Size size) {
		BR_ASSERT(s1 < s0 || s1 >= s0 + size);
		return reinterpret_cast< Char * >(std::memcpy(s0, s1, size));
	}

	static constexpr Char to_char(Int i) noexcept { return Char(i); }

	static constexpr Int to_int(Char c) noexcept { return Int(UInt8(c)); }

	static constexpr bool eq_int(Int i0, Int i1) noexcept { return i0 == i1; }

	static constexpr Int eof() noexcept { return Int(EOF); }

	static constexpr Int not_eof(Int i) noexcept { return eq_int(i, eof()) ? ~eof() : i; }
}; // struct CharTraits<NChar>

template <>
struct CharTraits<WChar> {
	using Char = WChar;
	using Int = UInt32;
	// TODO: using Offset = std::streamoff;
	// TODO: using Position = std::streampos;
	// TODO: using State = std::mbstate_t;

	static constexpr bool eq(Char c0, Char c1) noexcept { return c0 == c1; }
	static constexpr bool lt(Char c0, Char c1) noexcept { return c0 <  c1; }
	static constexpr bool eq_int(Int i0, Int i1) noexcept { return i0 == i1; }

	static Size length(CString<Char> s) {
		return std::wcslen(s);
	}

	static Relation compare(CString<Char> s0, CString<Char> s1, Size size) noexcept {
		return to_relation(std::wmemcmp(s0, s1, size));
	}

	static Char const * find(Char const * s, Size size, Char const & c) {
		return reinterpret_cast< Char const * >(std::wmemchr(s, c, size));
	}

	static void assign(Char & c0, Char const & c1) noexcept {
		c0 = c1;
	}

	static Char * assign(Char * s, Size size, Char c) {
		return reinterpret_cast< Char * >(std::wmemset(s, c, size));
	}

	static Char * move(Char * s0, CString<Char> s1, Size size) {
		return reinterpret_cast< Char * >(std::wmemmove(s0, s1, size));
	}

	static Char * copy(Char * s0, CString<Char> s1, Size size) {
		BR_ASSERT(s1 < s0 || s1 >= s0 + size);
		return reinterpret_cast< Char * >(std::wmemcpy(s0, s1, size));
	}

	static constexpr Char to_char(Int  i) noexcept { return Char(i); }
	static constexpr Int  to_int (Char c) noexcept { return Int (c); }

	static constexpr Int eof() noexcept { return Int(WEOF); }

	static constexpr Int not_eof(Int i) noexcept { return eq_int(i, eof()) ? ~eof() : i; }
}; // struct CharTraits<WChar>

template <>
struct CharTraits<Char16> {
	using Char = Char16;
	using Int = UInt16;
	// TODO: using Offset = std::streamoff;
	// TODO: using Position = std::u16streampos;
	// TODO: using State = std::mbstate_t;

	static constexpr bool eq(Char c0, Char c1) noexcept { return c0 == c1; }
	static constexpr bool lt(Char c0, Char c1) noexcept { return c0 <  c1; }
	static constexpr bool eq_int(Int i0, Int i1) noexcept { return i0 == i1; }

	static Size length(CString<Char> s) {
		Size result = 0;
		for (; !eq(*s, Char(0)); ++s) {
			++result;
		}
		return result;
	}

	static Relation compare(CString<Char> s0, CString<Char> s1, Size size) noexcept {
		for (; size > 0; --size, ++s0, ++s1) {
			if (lt(*s0, *s1)) { return Relation::LT; }
			if (lt(*s1, *s0)) { return Relation::GT; }
		}
		return Relation::EQ;
	}

	static Char const * find(Char const * s, Size size, Char const & c) {
		for (; size-- > 0; ++s) {
			if (eq(*s, c)) {
				return s;
			}
		}
		return nullptr;
	}

	static void assign(Char & c0, Char const & c1) noexcept {
		c0 = c1;
	}

	static Char * assign(Char * s, Size size, Char c) {
		Char * result = s;
		for (; size > 0; --size) {
			assign(*s++, c);
		}
		return result;
	}

	static Char * move(Char * s0, CString<Char> s1, Size size) {
		Char * result = s0;
		if (s0 < s1) {
			for (; size > 0; --size) {
				assign(*s0++, *s1++);
			}
		} else if (s1 < s0) {
			s0 += size;
			s1 += size;
			for (; size > 0; --size) {
				assign(*--s0, *--s1);
			}
		}
		return result;
	}

	static Char * copy(Char * s0, CString<Char> s1, Size size) {
		BR_ASSERT(s1 < s0 || s1 >= s0 + size);
		Char * result = s0;
		for (; size > 0; --size) {
			assign(*s0++, *s1++);
		}
		return result;
	}

	static constexpr Char to_char(Int  i) noexcept { return Char(i); }
	static constexpr Int  to_int (Char c) noexcept { return Int (c); }

	static constexpr Int eof() noexcept { return Int(0xDFFF); }

	static constexpr Int not_eof(Int i) noexcept { return eq_int(i, eof()) ? ~eof() : i; }
}; // struct CharTraits<Char16>

template <>
struct CharTraits<Char32> {
	using Char = Char32;
	using Int = UInt32;
	// TODO: using Offset = std::streamoff;
	// TODO: using Position = std::u32streampos;
	// TODO: using State = std::mbstate_t;

	static constexpr bool eq(Char c0, Char c1) noexcept { return c0 == c1; }
	static constexpr bool lt(Char c0, Char c1) noexcept { return c0 <  c1; }
	static constexpr bool eq_int(Int i0, Int i1) noexcept { return i0 == i1; }

	static Size length(CString<Char> s) {
		Size result = 0;
		for (; !eq(*s, Char(0)); ++s) {
			++result;
		}
		return result;
	}

	static Relation compare(CString<Char> s0, CString<Char> s1, Size size) noexcept {
		for (; size > 0; --size, ++s0, ++s1) {
			if (lt(*s0, *s1)) { return Relation::LT; }
			if (lt(*s1, *s0)) { return Relation::GT; }
		}
		return Relation::EQ;
	}

	static Char const * find(Char const * s, Size size, Char const & c) {
		for (; size-- > 0; ++s) {
			if (eq(*s, c)) {
				return s;
			}
		}
		return nullptr;
	}

	static void assign(Char & c0, Char const & c1) noexcept {
		c0 = c1;
	}

	static Char * assign(Char * s, Size size, Char c) {
		Char * result = s;
		for (; size > 0; --size) {
			assign(*s++, c);
		}
		return result;
	}

	static Char * move(Char * s0, CString<Char> s1, Size size) {
		Char * result = s0;
		if (s0 < s1) {
			for (; size > 0; --size) {
				assign(*s0++, *s1++);
			}
		} else if (s1 < s0) {
			s0 += size;
			s1 += size;
			for (; size > 0; --size) {
				assign(*--s0, *--s1);
			}
		}
		return result;
	}

	static Char * copy(Char * s0, CString<Char> s1, Size size) {
		BR_ASSERT(s1 < s0 || s1 >= s0 + size);
		Char * result = s0;
		for (; size > 0; --size) {
			assign(*s0++, *s1++);
		}
		return result;
	}

	static constexpr Char to_char(Int  i) noexcept { return Char(i); }
	static constexpr Int  to_int (Char c) noexcept { return Int (c); }

	static constexpr Int eof() noexcept { return Int(0xFFFFFFFF); }

	static constexpr Int not_eof(Int i) noexcept { return eq_int(i, eof()) ? ~eof() : i; }
}; // struct CharTraits<Char16>

} // namespace BR

