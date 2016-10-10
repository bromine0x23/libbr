#include "../test.hpp"
#include "../support/allocator.hpp"
#include <libbr/string/string.hpp>
#include <libbr/container/array.hpp>
#include <libbr/exception/index_exception.hpp>

using namespace BR;

using S = String<UTF8Encoding>;
using U8S = String<UTF8Encoding>;

TEST(String, DefaultConstruct) {
	S s();
}

TEST(String, CopyConstruct) {
	auto test = [](S s) {
		S ss = s;
		EXPECT_EQ(s, ss);
		EXPECT_LE(ss.size(), ss.capacity());
		EXPECT_EQ(s.allocator(), ss.allocator());
	};
	test(S());
	test(S("01"));
	test(S("01234567890123456789012345678901234567890123456789012345678901234567890123456789"));
}

TEST(String, MoveConstruct) {
	auto test = [](S s) {
		S s0 = s;
		S s1 = BR::move(s);
		EXPECT_EQ(s0, s1);
		EXPECT_LE(s1.size(), s1.capacity());
		EXPECT_EQ(s0.allocator(), s1.allocator());
	};
	test(S());
	test(S("01"));
	test(S("01234567890123456789012345678901234567890123456789012345678901234567890123456789"));
}

TEST(String, InitializerListConstruct) {
	auto test = [](S s0, S s1) {
		EXPECT_EQ(s0, s1);
	};
	test(S{}, S());
	test(S{'A', 'B'}, S("AB"));
	test(S{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}, S("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));

}

TEST(String, At) {
	EXPECT_THROW(S().at(0), IndexException);
	auto test = [](S s) {
		S const & cs = s;
		for (S::Size i = 0; i < cs.size(); ++i) {
			EXPECT_EQ(cs.at(i), 'A' + i);
			EXPECT_EQ(cs.at(i), s.at(i));
		}
		EXPECT_THROW(cs.at(cs.size()), IndexException);
	};
	test(S("AB"));
	test(S("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}

TEST(String, Index) {
	EXPECT_EQ('\0', S()[0]);
	auto test = [](S s) {
		S const & cs = s;
		for (S::Size i = 0; i < cs.size(); ++i) {
			EXPECT_EQ(cs[i], 'A' + i);
			EXPECT_EQ(cs[i], s[i]);
		}
		EXPECT_EQ('\0', cs[cs.size()]);
	};
	test(S("AB"));
	test(S("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}

TEST(String, Front) {
	// Empty String
	{
		S s("");
		S const & cs = s;
		EXPECT_EQ('\0', s.front());
		EXPECT_EQ('\0', cs.front());
	}
	// Small String
	{
		S s("0123");
		S const & cs = s;
		EXPECT_EQ(&s[0], &s.front());
		EXPECT_EQ(&cs[0], &cs.front());
		s.front() = S::Element('Z');
		EXPECT_EQ(S::Element('Z'), s.front());
	}
	// Large String
	{
		S s("01234567890123456789012345678901234567890123456789012345678901234567890123456789");
		S const & cs = s;
		EXPECT_EQ(&s[0], &s.front());
		EXPECT_EQ(&cs[0], &cs.front());
		s.front() = S::Element('Z');
		EXPECT_EQ(S::Element('Z'), s.front());
	}
}

TEST(String, Back) {
	// Small String
	{
		S s("0123");
		S const & cs = s;
		EXPECT_EQ(&s[s.size() - 1], &s.back());
		EXPECT_EQ(&cs[cs.size() - 1], &cs.back());
		s.back() = S::Element('Z');
		EXPECT_EQ(S::Element('Z'), s.back());
	}
	// Large String
	{
		S s("01234567890123456789012345678901234567890123456789012345678901234567890123456789");
		S const & cs = s;
		EXPECT_EQ(&s[s.size() - 1], &s.back());
		EXPECT_EQ(&cs[cs.size() - 1], &cs.back());
		s.back() = S::Element('Z');
		EXPECT_EQ(S::Element('Z'), s.back());
	}
}

TEST(String, Size) {
	auto test = [](S s, S::Size expected_length) {
		EXPECT_EQ(expected_length, s.length());
	};
	test(U8S(), 0);
	test(U8S(""), 0);
	test(U8S("0123"), 4);
	test(U8S("01234567890123456789012345678901234567890123456789012345678901234567890123456789"), 80);
	test(U8S(u8"高槻やよい"), 5);
}

TEST(String, Capacity) {
	auto test = [](S s, S::Size size) {
		EXPECT_GE(s.capacity(), size);
		EXPECT_GE(s.capacity(), s.size());
	};
	test(S(), 0);
	test(S(""), 0);
	test(S("0123"), 4);
	test(S("01234567890123456789012345678901234567890123456789012345678901234567890123456789"), 80);
}

TEST(String, Compare) {
	EXPECT_EQ(S(""), S());
	EXPECT_EQ(S(""), S(""));
	EXPECT_EQ(S(""), "");
	EXPECT_EQ(S("A"), S("A"));
	EXPECT_EQ(S("A"), "A");
	EXPECT_EQ(S("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	EXPECT_EQ(S("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	EXPECT_LT(S("ABC"), S("ABCDE"));
	EXPECT_LT(S("ABC"), "ABCDE");
	EXPECT_LT(S("ABCDEFGHIJKLMNOPQRSTUVWXY"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	EXPECT_LT(S("ABCDEFGHIJKLMNOPQRSTUVWXY"), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	EXPECT_GT(S("ABCDE"), S("ABC"));
	EXPECT_GT(S("ABCDE"), "ABC");
	EXPECT_GT(S("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), S("ABCDEFGHIJKLMNOPQRSTUVWXY"));
	EXPECT_GT(S("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "ABCDEFGHIJKLMNOPQRSTUVWXY");
}

TEST(String, CopyAssignment) {
	auto test = [](S s, S const & s0, S const & s1) {
		s = s0;
		EXPECT_EQ(s0.size(), s.size());
		EXPECT_EQ(s0.front(), s.front());
		EXPECT_EQ(s0, s);

		s.assign(s1);
		EXPECT_EQ(s1.size(), s.size());
		EXPECT_EQ(s1.front(), s.front());
		EXPECT_EQ(s1, s);
	};
	test(S(""), S("01"), S(""));
	test(S(""), S("01"), S("AB"));
	test(S(""), S("01"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(S(""), S("012345678901234567890123456789012345678901234567890123456789"), S(""));
	test(S(""), S("012345678901234567890123456789012345678901234567890123456789"), S("AB"));
	test(S(""), S("012345678901234567890123456789012345678901234567890123456789"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(S("ab"), S("01"), S(""));
	test(S("ab"), S("01"), S("AB"));
	test(S("ab"), S("01"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(S("ab"), S("012345678901234567890123456789012345678901234567890123456789"), S(""));
	test(S("ab"), S("012345678901234567890123456789012345678901234567890123456789"), S("AB"));
	test(S("ab"), S("012345678901234567890123456789012345678901234567890123456789"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("01"), S(""));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("01"), S("AB"));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("01"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("012345678901234567890123456789012345678901234567890123456789"), S(""));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("012345678901234567890123456789012345678901234567890123456789"), S("AB"));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("012345678901234567890123456789012345678901234567890123456789"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}

TEST(String, MoveAssignment) {
	auto test = [](S s, S s0, S s1) {
		S ss0 = s0;
		s = BR::move(s0);
		EXPECT_EQ(ss0.size(), s.size());
		EXPECT_EQ(ss0.front(), s.front());
		EXPECT_EQ(ss0, s);

		S ss1 = s1;
		s.assign(BR::move(s1));
		EXPECT_EQ(ss1.size(), s.size());
		EXPECT_EQ(ss1.front(), s.front());
		EXPECT_EQ(ss1, s);
	};
	test(S(""), S("01"), S(""));
	test(S(""), S("01"), S("AB"));
	test(S(""), S("01"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(S(""), S("012345678901234567890123456789012345678901234567890123456789"), S(""));
	test(S(""), S("012345678901234567890123456789012345678901234567890123456789"), S("AB"));
	test(S(""), S("012345678901234567890123456789012345678901234567890123456789"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(S("ab"), S("01"), S(""));
	test(S("ab"), S("01"), S("AB"));
	test(S("ab"), S("01"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(S("ab"), S("012345678901234567890123456789012345678901234567890123456789"), S(""));
	test(S("ab"), S("012345678901234567890123456789012345678901234567890123456789"), S("AB"));
	test(S("ab"), S("012345678901234567890123456789012345678901234567890123456789"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("01"), S(""));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("01"), S("AB"));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("01"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("012345678901234567890123456789012345678901234567890123456789"), S(""));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("012345678901234567890123456789012345678901234567890123456789"), S("AB"));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("012345678901234567890123456789012345678901234567890123456789"), S("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}

TEST(String, Append) {
	auto test = [](S x, S y, S z) {
		{
			S s(x);
			s << y;
			EXPECT_EQ(z.size(), s.size());
			EXPECT_EQ(z.front(), s.front());
			EXPECT_EQ(z, s);
		} {
			S s(x);
			s.append(y);
			EXPECT_EQ(z.size(), s.size());
			EXPECT_EQ(z.front(), s.front());
			EXPECT_EQ(z, s);
		}
	};
	test(S(""), S(""), S(""));
	test(S(""), S("0123"), S("0123"));
	test(S(""), S("01234567890123456789"), S("01234567890123456789"));
	test(S(""), S("0123456789012345678901234567890123456789"), S("0123456789012345678901234567890123456789"));
	test(S("abcd"), S(""), S("abcd"));
	test(S("abcd"), S("0123"), S("abcd0123"));
	test(S("abcd"), S("01234567890123456789"), S("abcd01234567890123456789"));
	test(S("abcd"), S("0123456789012345678901234567890123456789"), S("abcd0123456789012345678901234567890123456789"));
	test(S("abcdefghijklmn"), S(""), S("abcdefghijklmn"));
	test(S("abcdefghijklmn"), S("0123"), S("abcdefghijklmn0123"));
	test(S("abcdefghijklmn"), S("01234567890123456789"), S("abcdefghijklmn01234567890123456789"));
	test(S("abcdefghijklmn"), S("0123456789012345678901234567890123456789"), S("abcdefghijklmn0123456789012345678901234567890123456789"));
	test(S("abcdefghijklmnopqrstuvwxyz"), S(""), S("abcdefghijklmnopqrstuvwxyz"));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("0123"), S("abcdefghijklmnopqrstuvwxyz0123"));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("01234567890123456789"), S("abcdefghijklmnopqrstuvwxyz01234567890123456789"));
	test(S("abcdefghijklmnopqrstuvwxyz"), S("0123456789012345678901234567890123456789"), S("abcdefghijklmnopqrstuvwxyz0123456789012345678901234567890123456789"));
}

TEST(String, Insert) {
	auto test = [](S x, S::Size index, S y, S r) {
		EXPECT_NO_THROW({
			S s(x);
			s.insert(index, y);
			EXPECT_EQ(r, s);
		});
	};
	test("", 0, "", "");
	test("", 0, "01234", "01234");
	test("", 0, "0123456789", "0123456789");
	test("", 0, "01234567890123456789", "01234567890123456789");
	test("abcde", 0, "", "abcde");
	test("abcde", 0, "01234", "01234abcde");
	test("abcde", 0, "0123456789", "0123456789abcde");
	test("abcde", 0, "01234567890123456789", "01234567890123456789abcde");
	test("abcde", 3, "", "abcde");
	test("abcde", 3, "01234", "abc01234de");
	test("abcde", 3, "0123456789", "abc0123456789de");
	test("abcde", 3, "01234567890123456789", "abc01234567890123456789de");
	test("abcde", 5, "", "abcde");
	test("abcde", 5, "01234", "abcde01234");
	test("abcde", 5, "0123456789", "abcde0123456789");
	test("abcde", 5, "01234567890123456789", "abcde01234567890123456789");
	test("abcdefghij", 0, "", "abcdefghij");
	test("abcdefghij", 0, "01234", "01234abcdefghij");
	test("abcdefghij", 0, "0123456789", "0123456789abcdefghij");
	test("abcdefghij", 0, "01234567890123456789", "01234567890123456789abcdefghij");
	test("abcdefghij", 4, "", "abcdefghij");
	test("abcdefghij", 4, "01234", "abcd01234efghij");
	test("abcdefghij", 4, "0123456789", "abcd0123456789efghij");
	test("abcdefghij", 4, "01234567890123456789", "abcd01234567890123456789efghij");
	test("abcdefghij", 7, "", "abcdefghij");
	test("abcdefghij", 7, "01234", "abcdefg01234hij");
	test("abcdefghij", 7, "0123456789", "abcdefg0123456789hij");
	test("abcdefghij", 7, "01234567890123456789", "abcdefg01234567890123456789hij");
	test("abcdefghij", 10, "", "abcdefghij");
	test("abcdefghij", 10, "01234", "abcdefghij01234");
	test("abcdefghij", 10, "0123456789", "abcdefghij0123456789");
	test("abcdefghij", 10, "01234567890123456789", "abcdefghij01234567890123456789");
	test("abcdefghijklmnopqrstuvwxyz", 0, "", "abcdefghijklmnopqrstuvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 0, "01234", "01234abcdefghijklmnopqrstuvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 0, "0123456789", "0123456789abcdefghijklmnopqrstuvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 0, "01234567890123456789", "01234567890123456789abcdefghijklmnopqrstuvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 11, "", "abcdefghijklmnopqrstuvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 11, "01234", "abcdefghijk01234lmnopqrstuvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 11, "0123456789", "abcdefghijk0123456789lmnopqrstuvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 11, "01234567890123456789", "abcdefghijk01234567890123456789lmnopqrstuvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 20, "", "abcdefghijklmnopqrstuvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 20, "01234", "abcdefghijklmnopqrst01234uvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 20, "0123456789", "abcdefghijklmnopqrst0123456789uvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 20, "01234567890123456789", "abcdefghijklmnopqrst01234567890123456789uvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 26, "", "abcdefghijklmnopqrstuvwxyz");
	test("abcdefghijklmnopqrstuvwxyz", 26, "01234", "abcdefghijklmnopqrstuvwxyz01234");
	test("abcdefghijklmnopqrstuvwxyz", 26, "0123456789", "abcdefghijklmnopqrstuvwxyz0123456789");
	test("abcdefghijklmnopqrstuvwxyz", 26, "01234567890123456789", "abcdefghijklmnopqrstuvwxyz01234567890123456789");
}

TEST(String, Replace) {
	auto test = [](S x, S::Size index, S::Size length, S y, S r) {
		EXPECT_NO_THROW({
			{
				S s(x);
				s.replace(index, length, y);
				EXPECT_EQ(r, s);
			} {
				S s(x);
				s(index, length) = y;
				EXPECT_EQ(r, s);
			}
		});
	};
	test(S(""), 0, 0, S(""), S(""));
	test(S(""), 0, 0, S("01234"), S("01234"));
	test(S(""), 0, 0, ("0123456789"), S("0123456789"));
	test(S(""), 0, 0, S("012345678901234567890123456789"), S("012345678901234567890123456789"));
	test(S(""), 0, 1, S(""), S(""));
	test(S(""), 0, 1, S("01234"), S("01234"));
	test(S(""), 0, 1, S("0123456789"), S("0123456789"));
	test(S(""), 0, 1, S("012345678901234567890123456789"), S("012345678901234567890123456789"));
}

TEST(String, Remove) {
}

TEST(String, Complex0) {
	auto hash = [](UInt32 u, S p) {
		UInt8 n[4] = {};
		for (S::Size i = 0; i < p.size(); ++i) {
			n[i % 4] ^= p[i] & 0xFFU;
		}

		UInt8 v[4] = {};
		auto t = "ECOK"_s;
		for (S::Size i = 0; i < 4; ++i) {
			v[i] = UInt8((u >> ((3 - i) << 3) & 0xFFU) ^ t[i]);
		}

		UInt8 a[8];
		for (auto i = 0; i < 8; ++i) {
			a[i] = i % 2 == 0 ? n[i / 2] : v[i / 2];
		}

		auto d = "0123456789ABCDEF"_s;
		S r;
		for (auto i = 0; i < 8; ++i) {
			r << d[a[i] / 0x10U] << d[a[i] & 0x0FU];
		}

		return r;
	};

	EXPECT_EQ(hash(737527723, "RawString"), "416E13B61E883DE0");
	EXPECT_EQ(hash(491685152, "RawString"), "4158130D1ECA3D6B");
	EXPECT_EQ(hash(295011093, "RawString"), "415413D61ECC3D5E");
}