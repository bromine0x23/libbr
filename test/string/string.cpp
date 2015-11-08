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
	EXPECT_EQ(S("") << "", "");
	EXPECT_EQ(S("") << "01234", "01234");
	EXPECT_EQ(S("") << "0123456789", "0123456789");
	EXPECT_EQ(S("") << "01234567890123456789", "01234567890123456789");

	EXPECT_EQ(S("abcde") << "", "abcde");
	EXPECT_EQ(S("abcde") << "01234", "abcde01234");
	EXPECT_EQ(S("abcde") << "0123456789", "abcde0123456789");
	EXPECT_EQ(S("abcde") << "01234567890123456789", "abcde01234567890123456789");

	EXPECT_EQ(S("abcdefghij") << "", "abcdefghij");
	EXPECT_EQ(S("abcdefghij") << "01234", "abcdefghij01234");
	EXPECT_EQ(S("abcdefghij") << "0123456789", "abcdefghij0123456789");
	EXPECT_EQ(S("abcdefghij") << "01234567890123456789", "abcdefghij01234567890123456789");

	EXPECT_EQ(S("abcdefghijklmnopqrst") << "", "abcdefghijklmnopqrst");
	EXPECT_EQ(S("abcdefghijklmnopqrst") << "01234", "abcdefghijklmnopqrst01234");
	EXPECT_EQ(S("abcdefghijklmnopqrst") << "0123456789", "abcdefghijklmnopqrst0123456789");
	EXPECT_EQ(S("abcdefghijklmnopqrst") << "01234567890123456789", "abcdefghijklmnopqrst01234567890123456789");
}

TEST(TestString, Insert) {
	EXPECT_NO_THROW(EXPECT_EQ(S("")(0) << "", ""));
	EXPECT_NO_THROW(EXPECT_EQ(S("")(0) << '0', "0"));
	EXPECT_NO_THROW(EXPECT_EQ(S("")(0) << "01234", "01234"));
	EXPECT_NO_THROW(EXPECT_EQ(S("")(0) << "0123456789", "0123456789"));
	EXPECT_NO_THROW(EXPECT_EQ(S("")(0) << "01234567890123456789", "01234567890123456789"));

	EXPECT_THROW(S("")(1), IndexException);

	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(0) << "", "abcde"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(0) << '0', "0abcde"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(0) << "01234", "01234abcde"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(0) << "0123456789", "0123456789abcde"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(0) << "01234567890123456789", "01234567890123456789abcde"));

	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(3) << "", "abcde"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(3) << '0', "abc0de"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(3) << "01234", "abc01234de"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(3) << "0123456789", "abc0123456789de"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(3) << "01234567890123456789", "abc01234567890123456789de"));

	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(5) << "", "abcde"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(5) << '0', "abcde0"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(5) << "01234", "abcde01234"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(5) << "0123456789", "abcde0123456789"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcde")(5) << "01234567890123456789", "abcde01234567890123456789"));

	EXPECT_THROW(S("abcde")(6), IndexException);

	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(0) << "", "abcdefghij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(0) << '0', "0abcdefghij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(0) << "01234", "01234abcdefghij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(0) << "0123456789", "0123456789abcdefghij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(0) << "01234567890123456789", "01234567890123456789abcdefghij"));

	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(4) << "", "abcdefghij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(4) << '0', "abcd0efghij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(4) << "01234", "abcd01234efghij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(4) << "0123456789", "abcd0123456789efghij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(4) << "01234567890123456789", "abcd01234567890123456789efghij"));

	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(7) << "", "abcdefghij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(7) << '0', "abcdefg0hij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(7) << "01234", "abcdefg01234hij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(7) << "0123456789", "abcdefg0123456789hij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(7) << "01234567890123456789", "abcdefg01234567890123456789hij"));

	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(10) << "", "abcdefghij"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(10) << '0', "abcdefghij0"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(10) << "01234", "abcdefghij01234"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(10) << "0123456789", "abcdefghij0123456789"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghij")(10) << "01234567890123456789", "abcdefghij01234567890123456789"));

	EXPECT_THROW(S("abcdefghij")(11), IndexException);

	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(0) << "", "abcdefghijklmnopqrst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(0) << '0', "0abcdefghijklmnopqrst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(0) << "01234", "01234abcdefghijklmnopqrst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(0) << "0123456789", "0123456789abcdefghijklmnopqrst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(0) << "01234567890123456789", "01234567890123456789abcdefghijklmnopqrst"));

	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(11) << "", "abcdefghijklmnopqrst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(11) << '0', "abcdefghijk0lmnopqrst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(11) << "01234", "abcdefghijk01234lmnopqrst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(11) << "0123456789", "abcdefghijk0123456789lmnopqrst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(11) << "01234567890123456789", "abcdefghijk01234567890123456789lmnopqrst"));

	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(17) << "", "abcdefghijklmnopqrst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(17) << '0', "abcdefghijklmnopq0rst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(17) << "01234", "abcdefghijklmnopq01234rst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(17) << "0123456789", "abcdefghijklmnopq0123456789rst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(17) << "01234567890123456789", "abcdefghijklmnopq01234567890123456789rst"));

	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(20) << "", "abcdefghijklmnopqrst"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(20) << '0', "abcdefghijklmnopqrst0"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(20) << "01234", "abcdefghijklmnopqrst01234"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(20) << "0123456789", "abcdefghijklmnopqrst0123456789"));
	EXPECT_NO_THROW(EXPECT_EQ(S("abcdefghijklmnopqrst")(20) << "01234567890123456789", "abcdefghijklmnopqrst01234567890123456789"));

	EXPECT_THROW(S("abcdefghijklmnopqrst")(21), IndexException);
}