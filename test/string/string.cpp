#include "libbr/string/string.hpp"
#include "libbr/exception/index_exception.hpp"
#include <gtest/gtest.h>

using namespace BR;

using S = String<NChar>;

TEST(TestString, Compare) {
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

TEST(TestString, At) {
	EXPECT_THROW(S("").at(0), IndexException);
}

TEST(TestString, Append) {

	{
		S s("");
		s << "abcde";
		s << S("abcde");
	}

	auto test = [](CString<NChar> x, CString<NChar> y, CString<NChar> z) {
		S s(x);
		s << y;
		EXPECT_EQ(s, z);
	};

	test("", "", "");
	test("", "01234", "01234");
	test("", "0123456789", "0123456789");
	test("", "01234567890123456789", "01234567890123456789");

	test("abcde", "", "abcde");
	test("abcde", "01234", "abcde01234");
	test("abcde", "0123456789", "abcde0123456789");
	test("abcde", "01234567890123456789", "abcde01234567890123456789");

	test("abcdefghij", "", "abcdefghij");
	test("abcdefghij", "01234", "abcdefghij01234");
	test("abcdefghij", "0123456789", "abcdefghij0123456789");
	test("abcdefghij", "01234567890123456789", "abcdefghij01234567890123456789");

	test("abcdefghijklmnopqrst", "", "abcdefghijklmnopqrst");
	test("abcdefghijklmnopqrst", "01234", "abcdefghijklmnopqrst01234");
	test("abcdefghijklmnopqrst", "0123456789", "abcdefghijklmnopqrst0123456789");
	test("abcdefghijklmnopqrst", "01234567890123456789", "abcdefghijklmnopqrst01234567890123456789");

}

TEST(TestString, Insert) {

	auto test = [](CString<NChar> x, S::Size i, CString<NChar> y, CString<NChar> r) {
		EXPECT_NO_THROW({
			S s(x);
			s.insert(i, y);
			EXPECT_EQ(s, r);
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

	test("abcdefghijklmnopqrst", 0, "", "abcdefghijklmnopqrst");
	test("abcdefghijklmnopqrst", 0, "01234", "01234abcdefghijklmnopqrst");
	test("abcdefghijklmnopqrst", 0, "0123456789", "0123456789abcdefghijklmnopqrst");
	test("abcdefghijklmnopqrst", 0, "01234567890123456789", "01234567890123456789abcdefghijklmnopqrst");

	test("abcdefghijklmnopqrst", 11, "", "abcdefghijklmnopqrst");
	test("abcdefghijklmnopqrst", 11, "01234", "abcdefghijk01234lmnopqrst");
	test("abcdefghijklmnopqrst", 11, "0123456789", "abcdefghijk0123456789lmnopqrst");
	test("abcdefghijklmnopqrst", 11, "01234567890123456789", "abcdefghijk01234567890123456789lmnopqrst");

	test("abcdefghijklmnopqrst", 17, "", "abcdefghijklmnopqrst");
	test("abcdefghijklmnopqrst", 17, "01234", "abcdefghijklmnopq01234rst");
	test("abcdefghijklmnopqrst", 17, "0123456789", "abcdefghijklmnopq0123456789rst");
	test("abcdefghijklmnopqrst", 17, "01234567890123456789", "abcdefghijklmnopq01234567890123456789rst");

	test("abcdefghijklmnopqrst", 20, "", "abcdefghijklmnopqrst");
	test("abcdefghijklmnopqrst", 20, "01234", "abcdefghijklmnopqrst01234");
	test("abcdefghijklmnopqrst", 20, "0123456789", "abcdefghijklmnopqrst0123456789");
	test("abcdefghijklmnopqrst", 20, "01234567890123456789", "abcdefghijklmnopqrst01234567890123456789");

}