#include "test.hpp"

#include <libbr/iterators/advance.hpp>

using namespace BR;

TEST(Iterators, advance) {
	char string[] = "12345";
	{
		char * pointer = string + 2;
		advance(pointer, 2);
		EXPECT_EQ(string + 4, pointer);
	} {
		char * pointer = string + 2;
		advance(pointer, -2);
		EXPECT_EQ(string, pointer);
	}
}
