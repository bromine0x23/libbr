#pragma once

#include <cstdio>
#include <cwchar>
#include <libbr/config.hpp>
#include <libbr/assert.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/string/cstring.hpp>

namespace BR {

template< typename TChar >
struct CharTraits {
	using Char = TChar;

	static constexpr auto equal(Char x, Char y) noexcept -> bool {
		return x == y;
	}

	static constexpr auto less(Char x, Char y) noexcept -> bool {
		return x < y;
	}

	static void assign(Char & d, Char const & s) {
		s = d;
	}

	static auto compare(CString<Char> X, CString<Char> Y, Size n) noexcept -> Relation {
		for (; n > 0; --n, ++X, ++Y) {
			if (less(*X, *Y)) {
				return Relation::LT;
			}
			if (less(*Y, *X)) {
				return Relation::GT;
			}
		}
		return Relation::EQ;
	}

	static auto copy(Char * D, CString<Char> S, Size n) -> Char * {
		BR_ASSERT(S < D || S >= D + n);
		Char * R = D;
		for (; n > 0; --n) {
			assign(*D++, *S++);
		}
		return D;
	}

	static constexpr auto eof() noexcept -> Char {
		return Char(EOF);
	}

	static auto fill(Char * D, Size n, Char c) -> Char * {
		Char * R = D;
		for (; n > 0; --n) {
			assign(*D++, c);
		}
		return R;
	}

	static auto find(Char const * S, Char const & c, Size n) -> Char const * {
		for (; n-- > 0; ++S) {
			if (equal(*S, c)) {
				return S;
			}
		}
		return nullptr;
	}

	static auto length(CString<Char> S) -> Size {
		Size l = 0;
		for (; !equal(*S, Char(0)); ++S) {
			++l;
		}
		return l;
	}

	static auto move(Char * D, CString<Char> S, Size n) -> Char * {
		Char * R = D;
		if (D < S) {
			for (; n > 0; --n) {
				assign(*D++, *S++);
			}
		} else if (S < D) {
			D += n;
			S += n;
			for (; n > 0; --n) {
				assign(*--D, *--S);
			}
		}
		return R;
	}
}; // struct CharTraits<TChar>

template<>
struct CharTraits<NChar> {
	using Char = NChar;

	static constexpr auto equal(Char x, Char y) noexcept -> bool {
		return x == y;
	}

	static constexpr auto less(Char x, Char y) noexcept -> bool {
		return UInt8(x) < UInt8(y);
	}

	static void assign(Char & d, Char const & s) noexcept {
		d = s;
	}

	static auto compare(CString<Char> X, CString<Char> Y, Size n) noexcept -> Relation {
		return string_compare(X, Y, n);
	}

	static auto copy(Char * D, CString<Char> S, Size n) -> Char * {
		BR_ASSERT(S < D || S >= D + n);
		return string_copy(D, S, n);
	}

	static constexpr auto eof() noexcept -> Char {
		return Char(EOF);
	}

	static auto fill(Char * D, Size n, Char c) -> Char * {
		return string_fill(D, c, n);
	}

	static auto find(Char const * S, Char const & c, Size n) -> Char const * {
		return string_find(S, c, n);
	}

	static auto length(CString<Char> S) -> Size {
		return string_length(S);
	}

	static auto move(Char * D, CString<Char> S, Size n) -> Char * {
		return string_move(D, S, n);
	}
}; // struct CharTraits<NChar>

template<>
struct CharTraits<WChar> {
	using Char = WChar;

	static constexpr auto equal(Char x, Char y) noexcept -> bool {
		return x == y;
	}

	static constexpr auto less(Char x, Char y) noexcept -> bool {
		return x < y;
	}

	static void assign(Char & d, Char const & s) noexcept {
		d = s;
	}

	static auto compare(CString<Char> X, CString<Char> Y, Size n) noexcept -> Relation {
		return string_compare(X, Y, n);
	}

	static auto copy(Char * D, CString<Char> S, Size n) -> Char * {
		BR_ASSERT(S < D || S >= D + n);
		return string_copy(D, S, n);
	}

	static constexpr auto eof() noexcept -> Char {
		return Char(EOF);
	}

	static auto fill(Char * D, Size n, Char c) -> Char * {
		return string_fill(D, c, n);
	}

	static auto find(Char const * S, Char const & c, Size n) -> Char const * {
		return string_find(S, c, n);
	}

	static auto length(CString<Char> S) -> Size {
		return string_length(S);
	}

	static auto move(Char * D, CString<Char> S, Size n) -> Char * {
		return string_move(D, S, n);
	}
}; // struct CharTraits<NChar>

template <>
struct CharTraits<Char16> {
	using Char = Char16;

	static constexpr auto equal(Char c0, Char c1) noexcept -> bool {
		return c0 == c1;
	}

	static constexpr auto less(Char c0, Char c1) noexcept -> bool {
		return c0 <  c1;
	}

	static void assign(Char & c0, Char const & c1) noexcept {
		c0 = c1;
	}

	static auto compare(CString<Char> s0, CString<Char> s1, Size size) noexcept -> Relation {
		for (; size > 0; --size, ++s0, ++s1) {
			if (less(*s0, *s1)) {
				return Relation::LT;
			}
			if (less(*s1, *s0)) {
				return Relation::GT;
			}
		}
		return Relation::EQ;
	}

	static auto copy(Char * D, CString<Char> S, Size n) -> Char * {
		BR_ASSERT(S < D || S >= D + n);
		Char * R = D;
		for (; n > 0; --n) {
			assign(*D++, *S++);
		}
		return D;
	}

	static constexpr auto eof() noexcept -> Char {
		return Char(0xDFFF);
	}

	static auto fill(Char * D, Size n, Char c) -> Char * {
		Char * R = D;
		for (; n > 0; --n) {
			assign(*D++, c);
		}
		return R;
	}

	static auto find(Char const * S, Char const & c, Size n) -> Char const * {
		for (; n-- > 0; ++S) {
			if (equal(*S, c)) {
				return S;
			}
		}
		return nullptr;
	}

	static auto length(CString<Char> S) -> Size {
		Size l = 0;
		for (; !equal(*S, Char(0)); ++S) {
			++l;
		}
		return l;
	}

	static auto move(Char * D, CString<Char> S, Size n) -> Char * {
		Char * R = D;
		if (D < S) {
			for (; n > 0; --n) {
				assign(*D++, *S++);
			}
		} else if (S < D) {
			D += n;
			S += n;
			for (; n > 0; --n) {
				assign(*--D, *--S);
			}
		}
		return R;
	}
}; // struct CharTraits<Char16>

template <>
struct CharTraits<Char32> {
	using Char = Char32;

	static constexpr auto equal(Char c0, Char c1) noexcept -> bool {
		return c0 == c1;
	}

	static constexpr auto less(Char c0, Char c1) noexcept -> bool {
		return c0 <  c1;
	}

	static void assign(Char & c0, Char const & c1) noexcept {
		c0 = c1;
	}

	static auto compare(CString<Char> s0, CString<Char> s1, Size size) noexcept -> Relation {
		for (; size > 0; --size, ++s0, ++s1) {
			if (less(*s0, *s1)) {
				return Relation::LT;
			}
			if (less(*s1, *s0)) {
				return Relation::GT;
			}
		}
		return Relation::EQ;
	}

	static auto copy(Char * D, CString<Char> S, Size n) -> Char * {
		BR_ASSERT(S < D || S >= D + n);
		Char * R = D;
		for (; n > 0; --n) {
			assign(*D++, *S++);
		}
		return D;
	}

	static constexpr auto eof() noexcept -> Char {
		return Char(0xFFFFFFFF);
	}

	static auto fill(Char * D, Size n, Char c) -> Char * {
		Char * R = D;
		for (; n > 0; --n) {
			assign(*D++, c);
		}
		return R;
	}

	static auto find(Char const * S, Char const & c, Size n) -> Char const * {
		for (; n-- > 0; ++S) {
			if (equal(*S, c)) {
				return S;
			}
		}
		return nullptr;
	}

	static auto length(CString<Char> S) -> Size {
		Size l = 0;
		for (; !equal(*S, Char(0)); ++S) {
			++l;
		}
		return l;
	}

	static auto move(Char * D, CString<Char> S, Size n) -> Char * {
		Char * R = D;
		if (D < S) {
			for (; n > 0; --n) {
				assign(*D++, *S++);
			}
		} else if (S < D) {
			D += n;
			S += n;
			for (; n > 0; --n) {
				assign(*--D, *--S);
			}
		}
		return R;
	}
}; // struct CharTraits<Char16>

} // namespace BR

