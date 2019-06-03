#include "test.hpp"

#include <libbr/strings/string_compare.hpp>

using namespace BR;

TEST(Strings, string_compare) {
	NChar const * x = "123456789";
	NChar const * y = "123446789";

	EXPECT_EQ(Relation::GT, string_compare(x, y));
	EXPECT_EQ(Relation::EQ, string_compare(x, y, 4));
}
