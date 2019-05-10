#include "test.hpp"

#include <libbr/memory/memory_search.hpp>

using namespace BR;

TEST(Memory, memory_search) {
	char array[] = {'a','\0','a','A','a','a','A','a'};

	auto result = memory_search(array, 'A', sizeof(array));

	EXPECT_NE(nullptr, result);
}
