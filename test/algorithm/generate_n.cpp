#include "../test.hpp"
#include <libbr/algorithm/generate_n.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/distance.hpp>

using namespace BR;

TEST(Algorithm, generate_n) {
	{
		DynamicArray<int> array(5);

		int x = 0;

		generate_n(array.begin(), array.size(), [&x]{ return ++x; });

		EXPECT_EQ((DynamicArray<int>{ 1, 2, 3, 4, 5 }), array);
	} {
		DList<int> list(5);

		int x = 0;

		generate_n(list.begin(), list.size(), [&x]{ return ++x; });

		EXPECT_EQ((DList<int>{ 1, 2, 3, 4, 5 }), list);
	} {
		SList<int> list(5);

		int x = 0;

		generate_n(list.begin(), distance(list.begin(), list.end()), [&x]{ return ++x; });

		EXPECT_EQ((SList<int>{ 1, 2, 3, 4, 5 }), list);
	}
}
