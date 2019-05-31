#include "test.hpp"

#include <libbr/algorithms/search_last.hpp>

#include <libbr/functional/greater.hpp>
#include <libbr/functional/less.hpp>

using namespace BR;

TEST(Algorithms, search_last) {
	int source[] = { 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4 };
	int target[] = { 1, 2, 3 };

	EXPECT_EQ(source + 8, search_last(source, source + 12, target, target + 3));

	EXPECT_EQ(source + 9, search_last(source, source + 12, target, target + 3, Greater<>{}));

	EXPECT_EQ(source + 12, search_last(source, source + 12, target, target + 3, Less<>{}));
}
