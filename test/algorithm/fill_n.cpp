#include "../test.hpp"
#include <libbr/algorithm/fill_n.hpp>

#include <libbr/algorithm/all_of.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/distance.hpp>

using namespace BR;

TEST(Algorithm, fill_n) {
	{
		DynamicArray<int> array(10);

		fill_n(array.begin(), array.size(), 0x23);

		EXPECT_TRUE(all_of(array.cbegin(), array.cend(), [](auto x){ return x == 0x23; }));
	} {
		DList<int> list(10);

		fill_n(list.begin(), list.size(), 0x23);

		EXPECT_TRUE(all_of(list.cbegin(), list.cend(), [](auto x){ return x == 0x23; }));
	} {
		SList<int> list(10);

		fill_n(list.begin(), distance(list.cbegin(), list.cend()), 0x23);

		EXPECT_TRUE(all_of(list.cbegin(), list.cend(), [](auto x){ return x == 0x23; }));
	}
}
