#include "../test.hpp"
#include <libbr/algorithm/search_n.hpp>

#include <libbr/string/raw_string.hpp>

using namespace BR;

TEST(Algorithm, search_n) {
	{
		RawString<NChar> string = "1001010100010101001010101";

		EXPECT_EQ(string.cend(), search_n(string.cbegin(), string.cend(), 4, '0'));
	} {
		RawString<NChar> string = "1001010100010101001010101";

		EXPECT_NE(string.cend(), search_n(string.cbegin(), string.cend(), 3, '0'));
	}
}