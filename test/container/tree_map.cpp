#include "../test.hpp"
#include <libbr/container/tree_map.hpp>
#include <libbr/algorithm/all_of.hpp>

using namespace BR;

template class BR::TreeMap<int, int>;

TEST(TreeMap, DefaultConstruct) {
	TreeMap<int, int> tree;
	EXPECT_EQ(0, tree.size());
}

TEST(TreeMap, InitializerListConstruct) {
	TreeMap<int, int> tree{ {1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, 5} };
	EXPECT_EQ(5, tree.size());
	EXPECT_TRUE(all_of(tree.begin(), tree.end(), [](auto const & pair){ return pair.first + pair.second == 0; }));
}

TEST(TreeMap, Index) {
	TreeMap<int, int> tree;
	tree[0] = 1;
	tree[1] = 0;
	tree[2] = -1;
	tree[3] = -2;
	tree[4] = -3;
	tree[5] = -4;
	EXPECT_EQ(6, tree.size());
	EXPECT_TRUE(all_of(tree.begin(), tree.end(), [](auto const & pair){ return pair.first + pair.second == 1; }));
}
