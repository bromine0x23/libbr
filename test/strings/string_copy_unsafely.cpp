#include "test.hpp"

#include <libbr/strings/string_copy_unsafely.hpp>

using namespace BR;

TEST(Strings, string_copy_unsafely) {
	char const source[] = "1234567890";

	char destination[21] = {};

	string_copy_unsafely(source, destination);

	EXPECT_STREQ(destination, "1234567890");

	string_copy_unsafely(source, destination + 9, 5);

	EXPECT_STREQ(destination, "12345678912345");
}
