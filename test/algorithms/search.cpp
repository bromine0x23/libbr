#include "test.hpp"

#include <libbr/algorithms/search.hpp>

#include <libbr/functional/greater.hpp>

using namespace BR;

TEST(Algorithms, search) {
	int source[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int members[] = { 4, 5, 6 };

	EXPECT_EQ(source, search(source, source + 9, members, members));

	EXPECT_EQ(source + 3, search(source, source + 9, members, members + 3));

	EXPECT_EQ(source + 4, search(source, source + 9, members, members + 3, Greater<>{}));

	EXPECT_EQ(source + 2, search(source, source + 2, members, members + 3));

	EXPECT_EQ(source + 5, search(source, source + 5, members, members + 3));
}