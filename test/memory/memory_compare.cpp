#include "test.hpp"

#include <libbr/memory/memory_compare.hpp>

using namespace BR;

TEST(Memory, memory_compare) {
	char x[] = "123456789";
	char y[] = "123456780";

	EXPECT_EQ(Relation::GT, memory_compare(x, y, sizeof(x)));
}
