#include "test.hpp"

#include <libbr/algorithms/merge.hpp>

#include <libbr/algorithms/is_sorted.hpp>

using namespace BR;

TEST(Algorithms, merge) {
	{
		CArray<int, 5> source0 = {0, 2, 4, 6, 7};
		CArray<int, 5> source1 = {1, 3, 5, 8, 9};
		CArray<int, 10> target;

		EXPECT_TRUE(is_sorted(source0, source0 + 5));
		EXPECT_TRUE(is_sorted(source1, source1 + 5));

		auto end = merge(source0, source0 + 5, source1, source1 + 5, target);

		EXPECT_EQ(target + 10, end);
		EXPECT_TRUE(is_sorted(target, end));
	}
	{
		CArray<int, 4> source0 = {2, 3, 5, 7};
		CArray<int, 5> source1 = {1, 3, 5, 7, 9};
		CArray<int, 9> target;

		EXPECT_TRUE(is_sorted(source0, source0 + 4));
		EXPECT_TRUE(is_sorted(source1, source1 + 5));

		auto end = merge(source0, source0 + 4, source1, source1 + 5, target);

		EXPECT_EQ(target + 9, end);
		EXPECT_TRUE(is_sorted(target, end));
	}
	{
		CArray<int, 6> source0 = {1, 2, 4, 5, 7, 8};
		CArray<int, 4> source1 = {0, 3, 6, 9};
		CArray<int, 10> target;

		EXPECT_TRUE(is_sorted(source0, source0 + 6));
		EXPECT_TRUE(is_sorted(source1, source1 + 4));

		auto end = merge(source0, source0 + 6, source1, source1 + 4, target);

		EXPECT_EQ(target + 10, end);
		EXPECT_TRUE(is_sorted(target, end));
	}
	{
		CArray<int, 5> source0 = {0, 1, 2, 3, 4};
		CArray<int, 0> source1 = {};
		CArray<int, 5> target;

		auto end = merge(source0, source0 + 5, source1, source1, target);

		EXPECT_EQ(target + 5, end);
	}

}
