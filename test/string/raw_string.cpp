#include "../test.hpp"
#include "../support/allocator.hpp"
#include <libbr/string/raw_string.hpp>
#include <libbr/exception/index_exception.hpp>

using namespace BR;

using NS = RawString<NChar>;
using WS = RawString<WChar>;

TEST(RawString, At) {
	{
		EXPECT_THROW(NS().at(0), IndexException);
		auto test = [](NS s) {
			NS const & cs = s;
			for (NS::Size i = 0; i < cs.size(); ++i) {
				EXPECT_EQ(cs.at(i), 'A' + i);
				EXPECT_EQ(cs.at(i), s.at(i));
			}
			EXPECT_THROW(cs.at(cs.size()), IndexException);
		};
		test(NS("AB"));
		test(NS("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	} {
		EXPECT_THROW(WS().at(0), IndexException);
		auto test = [](WS s) {
			WS const & cs = s;
			for (WS::Size i = 0; i < cs.size(); ++i) {
				EXPECT_EQ(cs.at(i), L'A' + i);
				EXPECT_EQ(cs.at(i), s.at(i));
			}
			EXPECT_THROW(cs.at(cs.size()), IndexException);
		};
		test(WS(L"AB"));
		test(WS(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	}
}

TEST(RawString, Index) {
	{
		EXPECT_EQ('\0', NS()[0]);
		auto test = [](NS s) {
			NS const & cs = s;
			for (NS::Size i = 0; i < cs.size(); ++i) {
				EXPECT_EQ(cs[i], 'A' + i);
				EXPECT_EQ(cs[i], s[i]);
			}
			EXPECT_EQ('\0', cs[cs.size()]);
		};
		test(NS("AB"));
		test(NS("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	} {
		EXPECT_EQ(L'\0', WS()[0]);
		auto test = [](WS s) {
			WS const & cs = s;
			for (WS::Size i = 0; i < cs.size(); ++i) {
				EXPECT_EQ(cs[i], L'A' + i);
				EXPECT_EQ(cs[i], s[i]);
			}
			EXPECT_EQ(L'\0', cs[cs.size()]);
		};
		test(WS(L"AB"));
		test(WS(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	}

}

TEST(RawString, Front) {
	// Empty String
	{
		NS s("");
		NS const & cs = s;
		EXPECT_EQ('\0', s.front());
		EXPECT_EQ('\0', cs.front());
	}
	// Small String
	{
		NS s("0123");
		NS const & cs = s;
		EXPECT_EQ(&s[0], &s.front());
		EXPECT_EQ(&cs[0], &cs.front());
		s.front() = NS::Element('Z');
		EXPECT_EQ(NS::Element('Z'), s.front());
	}
	// Large String
	{
		NS s("01234567890123456789012345678901234567890123456789012345678901234567890123456789");
		NS const & cs = s;
		EXPECT_EQ(&s[0], &s.front());
		EXPECT_EQ(&cs[0], &cs.front());
		s.front() = NS::Element('Z');
		EXPECT_EQ(NS::Element('Z'), s.front());
	}
}

TEST(RawString, Back) {
	// Small String
	{
		NS s("0123");
		NS const & cs = s;
		EXPECT_EQ(&s[s.size() - 1], &s.back());
		EXPECT_EQ(&cs[cs.size() - 1], &cs.back());
		s.back() = NS::Element('Z');
		EXPECT_EQ(NS::Element('Z'), s.back());
	}
	// Large String
	{
		NS s("01234567890123456789012345678901234567890123456789012345678901234567890123456789");
		NS const & cs = s;
		EXPECT_EQ(&s[s.size() - 1], &s.back());
		EXPECT_EQ(&cs[cs.size() - 1], &cs.back());
		s.back() = NS::Element('Z');
		EXPECT_EQ(NS::Element('Z'), s.back());
	}
}

TEST(RawString, Size) {
	auto test = [](NS s, NS::Size expected_size) {
		EXPECT_EQ(expected_size, s.size());
	};
	test(NS(), 0);
	test(""_rs, 0);
	test("0123"_rs, 4);
	test("01234567890123456789012345678901234567890123456789012345678901234567890123456789"_rs, 80);
	test("abc\0\0abc"_rs, 8);
	test(u8"高槻やよい"_rs, 15);
}

TEST(RawString, Capacity) {
	auto test = [](NS s, NS::Size size) {
		EXPECT_GE(s.capacity(), size);
		EXPECT_GE(s.capacity(), s.size());
	};
	test(NS(), 0);
	test(NS(""), 0);
	test(NS("0123"), 4);
	test(NS("01234567890123456789012345678901234567890123456789012345678901234567890123456789"), 80);
}

TEST(RawString, Compare) {
	EXPECT_EQ(NS(""), NS());
	EXPECT_EQ(NS(""), NS(""));
	EXPECT_EQ(NS(""), "");
	EXPECT_EQ(NS("A"), NS("A"));
	EXPECT_EQ(NS("A"), "A");
	EXPECT_EQ(NS("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	EXPECT_EQ(NS("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	EXPECT_LT(NS("ABC"), NS("ABCDE"));
	EXPECT_LT(NS("ABC"), "ABCDE");
	EXPECT_LT(NS("ABCDEFGHIJKLMNOPQRSTUVWXY"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	EXPECT_LT(NS("ABCDEFGHIJKLMNOPQRSTUVWXY"), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	EXPECT_GT(NS("ABCDE"), NS("ABC"));
	EXPECT_GT(NS("ABCDE"), "ABC");
	EXPECT_GT(NS("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), NS("ABCDEFGHIJKLMNOPQRSTUVWXY"));
	EXPECT_GT(NS("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "ABCDEFGHIJKLMNOPQRSTUVWXY");
}

TEST(RawString, CopyAssignment) {
	auto test = [](NS s, NS const & s0, NS const & s1) {
		s = s0;
		EXPECT_EQ(s0.size(), s.size());
		EXPECT_EQ(s0.front(), s.front());
		EXPECT_EQ(s0, s);

		s.assign(s1);
		EXPECT_EQ(s1.size(), s.size());
		EXPECT_EQ(s1.front(), s.front());
		EXPECT_EQ(s1, s);
	};
	test(NS(""), NS("01"), NS(""));
	test(NS(""), NS("01"), NS("AB"));
	test(NS(""), NS("01"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(NS(""), NS("012345678901234567890123456789012345678901234567890123456789"), NS(""));
	test(NS(""), NS("012345678901234567890123456789012345678901234567890123456789"), NS("AB"));
	test(NS(""), NS("012345678901234567890123456789012345678901234567890123456789"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(NS("ab"), NS("01"), NS(""));
	test(NS("ab"), NS("01"), NS("AB"));
	test(NS("ab"), NS("01"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(NS("ab"), NS("012345678901234567890123456789012345678901234567890123456789"), NS(""));
	test(NS("ab"), NS("012345678901234567890123456789012345678901234567890123456789"), NS("AB"));
	test(NS("ab"), NS("012345678901234567890123456789012345678901234567890123456789"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("01"), NS(""));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("01"), NS("AB"));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("01"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("012345678901234567890123456789012345678901234567890123456789"), NS(""));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("012345678901234567890123456789012345678901234567890123456789"), NS("AB"));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("012345678901234567890123456789012345678901234567890123456789"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}

TEST(RawString, MoveAssignment) {
	auto test = [](NS s, NS s0, NS s1) {
		NS ss0 = s0;
		s = BR::move(s0);
		EXPECT_EQ(ss0.size(), s.size());
		EXPECT_EQ(ss0.front(), s.front());
		EXPECT_EQ(ss0, s);

		NS ss1 = s1;
		s.assign(BR::move(s1));
		EXPECT_EQ(ss1.size(), s.size());
		EXPECT_EQ(ss1.front(), s.front());
		EXPECT_EQ(ss1, s);
	};
	test(NS(""), NS("01"), NS(""));
	test(NS(""), NS("01"), NS("AB"));
	test(NS(""), NS("01"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(NS(""), NS("012345678901234567890123456789012345678901234567890123456789"), NS(""));
	test(NS(""), NS("012345678901234567890123456789012345678901234567890123456789"), NS("AB"));
	test(NS(""), NS("012345678901234567890123456789012345678901234567890123456789"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(NS("ab"), NS("01"), NS(""));
	test(NS("ab"), NS("01"), NS("AB"));
	test(NS("ab"), NS("01"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(NS("ab"), NS("012345678901234567890123456789012345678901234567890123456789"), NS(""));
	test(NS("ab"), NS("012345678901234567890123456789012345678901234567890123456789"), NS("AB"));
	test(NS("ab"), NS("012345678901234567890123456789012345678901234567890123456789"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("01"), NS(""));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("01"), NS("AB"));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("01"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("012345678901234567890123456789012345678901234567890123456789"), NS(""));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("012345678901234567890123456789012345678901234567890123456789"), NS("AB"));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("012345678901234567890123456789012345678901234567890123456789"), NS("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}

TEST(RawString, Append) {
	auto test = [](NS x, NS y, NS z) {
		{
			NS s(x);
			s << y;
			EXPECT_EQ(z.size(), s.size());
			EXPECT_EQ(z.front(), s.front());
			EXPECT_EQ(z, s);
		} {
			NS s(x);
			s.append(y);
			EXPECT_EQ(z.size(), s.size());
			EXPECT_EQ(z.front(), s.front());
			EXPECT_EQ(z, s);
		}
	};
	test(NS(""), NS(""), NS(""));
	test(NS(""), NS("0123"), NS("0123"));
	test(NS(""), NS("01234567890123456789"), NS("01234567890123456789"));
	test(NS(""), NS("0123456789012345678901234567890123456789"), NS("0123456789012345678901234567890123456789"));
	test(NS("abcd"), NS(""), NS("abcd"));
	test(NS("abcd"), NS("0123"), NS("abcd0123"));
	test(NS("abcd"), NS("01234567890123456789"), NS("abcd01234567890123456789"));
	test(NS("abcd"), NS("0123456789012345678901234567890123456789"), NS("abcd0123456789012345678901234567890123456789"));
	test(NS("abcdefghijklmn"), NS(""), NS("abcdefghijklmn"));
	test(NS("abcdefghijklmn"), NS("0123"), NS("abcdefghijklmn0123"));
	test(NS("abcdefghijklmn"), NS("01234567890123456789"), NS("abcdefghijklmn01234567890123456789"));
	test(NS("abcdefghijklmn"), NS("0123456789012345678901234567890123456789"), NS("abcdefghijklmn0123456789012345678901234567890123456789"));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS(""), NS("abcdefghijklmnopqrstuvwxyz"));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("0123"), NS("abcdefghijklmnopqrstuvwxyz0123"));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("01234567890123456789"), NS("abcdefghijklmnopqrstuvwxyz01234567890123456789"));
	test(NS("abcdefghijklmnopqrstuvwxyz"), NS("0123456789012345678901234567890123456789"), NS("abcdefghijklmnopqrstuvwxyz0123456789012345678901234567890123456789"));
}

TEST(RawString, Insert) {
	auto test = [](NS x, NS::Size index, NS y, NS r) {
		EXPECT_NO_THROW({
			NS s(x);
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

TEST(RawString, Replace) {
	auto test = [](NS x, NS::Size index, NS::Size length, NS y, NS r) {
		EXPECT_NO_THROW({
			{
				NS s(x);
				s.replace(index, length, y);
				EXPECT_EQ(r, s);
			} {
				NS s(x);
				s(index, length) = y;
				EXPECT_EQ(r, s);
			}
		});
	};
	test(NS(""), 0, 0, NS(""), NS(""));
	test(NS(""), 0, 0, NS("01234"), NS("01234"));
	test(NS(""), 0, 0, NS("0123456789"), NS("0123456789"));
	test(NS(""), 0, 0, NS("012345678901234567890123456789"), NS("012345678901234567890123456789"));
	test(NS(""), 0, 1, NS(""), NS(""));
	test(NS(""), 0, 1, NS("01234"), NS("01234"));
	test(NS(""), 0, 1, NS("0123456789"), NS("0123456789"));
	test(NS(""), 0, 1, NS("012345678901234567890123456789"), NS("012345678901234567890123456789"));
}

TEST(RawString, Remove) {
}

TEST(RawString, Complex0) {
	auto hash = [](UInt32 u, NS p) {
		UInt8 n[4] = {};
		for (NS::Size i = 0; i < p.size(); ++i) {
			n[i % 4] ^= p[i] & 0xFFU;
		}

		UInt8 v[4] = {};
		auto t = "ECOK"_rs;
		for (NS::Size i = 0; i < 4; ++i) {
			v[i] = UInt8((u >> ((3 - i) << 3) & 0xFFU) ^ t[i]);
		}

		UInt8 a[8];
		for (auto i = 0; i < 8; ++i) {
			a[i] = i % 2 == 0 ? n[i / 2] : v[i / 2];
		}

		auto d = "0123456789ABCDEF"_rs;
		NS r;
		for (auto i = 0; i < 8; ++i) {
			r << d[a[i] / 0x10U] << d[a[i] & 0x0FU];
		}

		return r;
	};

	EXPECT_EQ(hash(737527723, "RawString"), "416E13B61E883DE0");
	EXPECT_EQ(hash(491685152, "RawString"), "4158130D1ECA3D6B");
	EXPECT_EQ(hash(295011093, "RawString"), "415413D61ECC3D5E");
}