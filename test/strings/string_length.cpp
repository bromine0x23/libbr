#include "test.hpp"

#include <libbr/strings/string_length.hpp>

using namespace BR;

TEST(Strings, string_length) {
	NChar const * string = "string";

	EXPECT_EQ(6, string_length(string));
}
