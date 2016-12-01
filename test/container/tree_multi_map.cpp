#include "../test.hpp"
#include <libbr/container/tree_multi_map.hpp>
#include <libbr/algorithm/all_of.hpp>

using namespace BR;

#if defined(BR_DEBUG)
template class BR::TreeMultiMap<int, int>;
#endif

TEST(TreeMultiMap, DefaultConstruct) {
	TreeMultiMap<int, int> tree;
	EXPECT_EQ(0, tree.size());
}

TEST(TreeMultiMap, InitializerListConstruct) {
	TreeMultiMap<int, int> tree{ {1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {2, -2}, {4, -4} };
	EXPECT_EQ(7, tree.size());
	EXPECT_TRUE(all_of(tree.begin(), tree.end(), [](Pair<int, int> const & pair){ return pair.first + pair.second == 0; }));
}

TEST(TreeMultiMap, Index) {
	TreeMultiMap<int, int> tree;
	tree.emplace(1, 0);
	tree.emplace(1, -1);
	tree.emplace(2, -1);
	tree.emplace(2, -2);
	tree.emplace(3, -2);
	tree.emplace(3, -3);
	tree.emplace(4, -3);
	tree.emplace(4, -4);
	tree.emplace(5, -4);
	tree.emplace(5, -5);
	EXPECT_EQ(10, tree.size());
	EXPECT_TRUE(all_of(tree.begin(), tree.end(), [](Pair<int, int> const & pair){ return (pair.first + pair.second) == 1 || (pair.first + pair.second) == 0; }));
}