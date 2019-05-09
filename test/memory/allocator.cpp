#include "test.hpp"

#include <libbr/memory/allocator.hpp>

using namespace BR;

TEST(Memory, Allocator) {
	EXPECT_TRUE(Allocator<int>::IS_ALWAYS_EQUAL);
	EXPECT_TRUE(Allocator<int>::IS_PROPAGATE_ON_CONTAINER_MOVE_ASSIGNMENT);

	Allocator<int> allocator;

	Size size = 5;

	int * p = allocator.allocate(size);

	EXPECT_NE(nullptr, p);

	allocator.deallocate(p, size);

	Allocator<double> other_allocator;

	EXPECT_EQ(allocator, other_allocator);
}

