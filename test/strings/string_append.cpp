#include "test.hpp"

#include <libbr/strings/string_append.hpp>

using namespace BR;

TEST(Strings, string_append) {
	char const source[] = "1234567890";

	char destination[30] = "abcde";

	string_append(destination, source);

	EXPECT_STREQ(destination, "abcde1234567890");

	string_append(destination, source, 5);

	EXPECT_STREQ(destination, "abcde123456789012345");
}
