#include "../test.hpp"
#include <libbr/algorithm/fill.hpp>

#include <libbr/algorithm/all_of.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

TEST(Algorithm, fill) {
	{
		DynamicArray<int> array(10);

		fill(array.begin(), array.end(), 0x23);

		EXPECT_TRUE(all_of(array.cbegin(), array.cend(), [](auto x){ return x == 0x23; }));
	} {
		DList<int> list(10);

		fill(list.begin(), list.end(), 0x23);

		EXPECT_TRUE(all_of(list.cbegin(), list.cend(), [](auto x){ return x == 0x23; }));
	} {
		SList<int> list(10);

		fill(list.begin(), list.end(), 0x23);

		EXPECT_TRUE(all_of(list.cbegin(), list.cend(), [](auto x){ return x == 0x23; }));
	}
}
