#include "../test.hpp"
#include <libbr/algorithm/search.hpp>

#include <libbr/string/raw_string.hpp>

using namespace BR;

TEST(Algorithm, search) {
	{
		RawString<NChar> string = "why waste time learning, when ignorance is instantaneous?";

		RawString<NChar> target = "learning";

		EXPECT_NE(string.cend(), search(string.cbegin(), string.cend(), target.cbegin(), target.cend()));
	} {
		RawString<NChar> string = "why waste time learning, when ignorance is instantaneous?";

		RawString<NChar> target = "lemming";

		EXPECT_EQ(string.cend(), search(string.cbegin(), string.cend(), target.cbegin(), target.cend()));
	}
}