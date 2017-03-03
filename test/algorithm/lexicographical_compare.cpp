#include "../test.hpp"
#include <libbr/algorithm/lexicographical_compare.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, lexicographical_compare) {
	{
		DynamicArray<int> array0{ 1, 2, 3, 4, 5 };
		DynamicArray<int> array1{ 1, 2, 3, 5, 4 };

		EXPECT_TRUE(lexicographical_compare(array0.cbegin(), array0.cend(), array1.cbegin(), array1.cend()));
	} {
		DList<int> list0{ 1, 2, 3, 4, 5 };
		DList<int> list1{ 1, 2, 3, 5, 4 };

		EXPECT_TRUE(lexicographical_compare(list0.cbegin(), list0.cend(), list1.cbegin(), list1.cend()));
	} {
		SList<int> list0{ 1, 2, 3, 4, 5 };
		SList<int> list1{ 1, 2, 3, 5, 4 };

		EXPECT_TRUE(lexicographical_compare(list0.cbegin(), list0.cend(), list1.cbegin(), list1.cend()));
	}
}
