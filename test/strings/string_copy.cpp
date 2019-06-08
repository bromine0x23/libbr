#include "test.hpp"

#include <libbr/strings/string_copy.hpp>

using namespace BR;

TEST(Strings, string_copy) {
	char string[] = "1234567890";

	string_copy(string + 3, string + 4, 3);

	EXPECT_STREQ(string, "1234456890");
}
