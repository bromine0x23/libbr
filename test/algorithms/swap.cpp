#include "test.hpp"

#include <libbr/algorithms/swap.hpp>

using namespace BR;

TEST(Algorithms, swap) {
	{
		int lhs[] = { 1, 2, 3, 4, 5 };
		int rhs[] = { -1, -2, -3, -4, -5, -6, -7, -8, -9 };

		swap(lhs, lhs + 5, rhs);
		EXPECT_EQ(-1 , lhs[0]);
		EXPECT_EQ(-5 , lhs[4]);
		EXPECT_EQ( 1, rhs[0]);
		EXPECT_EQ( 5, rhs[4]);
		EXPECT_EQ(-6 , rhs[5]);
		EXPECT_EQ(-9 , rhs[8]);
	} {
		int lhs[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int rhs[] = { -1, -2, -3, -4, -5 };

		swap(lhs, lhs + 9, rhs, rhs + 5);
		EXPECT_EQ(-1, lhs[0]);
		EXPECT_EQ(-5, lhs[4]);
		EXPECT_EQ( 6, lhs[5]);
		EXPECT_EQ( 9, lhs[8]);
		EXPECT_EQ( 1, rhs[0]);
		EXPECT_EQ( 5, rhs[4]);
	}
}