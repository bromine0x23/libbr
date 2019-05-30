#include "test.hpp"

#include <libbr/algorithms/replace_copy.hpp>

using namespace BR;

TEST(Algorithms, replace_copy) {

	int source[] = { 1, 2, 3, 4, 2, 2, 3, 4 };

	int replaced[8] = {};

	auto end = replace_copy(source, source + 8, replaced, 2, 22);

	EXPECT_EQ(end, replaced + 8);

	EXPECT_EQ( 1, replaced[0]);
	EXPECT_EQ(22, replaced[1]);
	EXPECT_EQ( 3, replaced[2]);
	EXPECT_EQ( 4, replaced[3]);
	EXPECT_EQ(22, replaced[4]);
	EXPECT_EQ(22, replaced[5]);
	EXPECT_EQ( 3, replaced[6]);
	EXPECT_EQ( 4, replaced[7]);
}
