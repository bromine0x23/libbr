#include "../test.hpp"
#include <libbr/algorithm/mismatch.hpp>

#include <libbr/iterator/distance.hpp>
#include <libbr/string/raw_string.hpp>

using namespace BR;

TEST(Algorithm, mismatch) {
	{
		RawString<NChar> string("abXYZba");

		auto pair = mismatch(string.cbegin(), string.cend(), string.crbegin());

		EXPECT_EQ(2, distance(string.cbegin(), pair.first));
	} {
		RawString<NChar> string("aba");

		auto pair = mismatch(string.cbegin(), string.cend(), string.crbegin());

		EXPECT_EQ(3, distance(string.cbegin(), pair.first));
	}
}