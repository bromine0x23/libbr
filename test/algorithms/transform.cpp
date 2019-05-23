#include "test.hpp"

#include <libbr/algorithms/transform.hpp>

using namespace BR;

TEST(Algorithms, transform) {
	{
		int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		transform(array, array + 10, array, [](int x){ return x + x; });

		EXPECT_EQ(0, array[0]);
		EXPECT_EQ(10, array[5]);
		EXPECT_EQ(18, array[9]);
	} {
		int array0[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int array1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int array2[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		transform(array0, array0 + 10, array0, [](int x, int y, int z){ return x * y + z; }, array1, array2);

		EXPECT_EQ(0, array0[0]);
		EXPECT_EQ(30, array0[5]);
		EXPECT_EQ(90, array0[9]);
	}
}