#include "../test.hpp"
#include <libbr/container/splay_tree.hpp>
#include <libbr/algorithm/accumulate.hpp>
#include <libbr/iterator/begin.hpp>
#include <libbr/iterator/end.hpp>

using namespace BR;

template class BR::SplayTree<int>;


TEST(SplayTree, DefaultConstruct) {
	SplayTree<int> tree;
	EXPECT_EQ(0, tree.size());
}

TEST(SplayTree, InitializerListConstruct) {
	SplayTree<int> tree{1, 2, 3, 4, 5, 6, 7, 8, 9};
	EXPECT_EQ(9, tree.size());
	EXPECT_EQ(45, accumulate(tree.begin(), tree.end(), 0));
}
TEST(SplayTree, RangeConstruct) {
	int values[9] = { 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	SplayTree<int> tree(begin(values), end(values));
	EXPECT_EQ(9, tree.size());
}

TEST(SplayTree, InsertEqual) {
	int values[9] = { 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	SplayTree<int> tree;
	tree.insert_equal(begin(values), end(values));
	EXPECT_EQ(9, tree.size());
}

TEST(SplayTree, CopyConstruct) {
SplayTree<int> tree0{ 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	SplayTree<int> tree1(tree0);
	EXPECT_EQ(9, tree0.size());
	EXPECT_EQ(9, tree1.size());
}

TEST(SplayTree, MoveConstruct) {
SplayTree<int> tree0{ 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	SplayTree<int> tree1(move(tree0));
	EXPECT_EQ(0, tree0.size());
	EXPECT_EQ(9, tree1.size());
}

TEST(SplayTree, Insert) {
	SplayTree<int> tree{5};
	tree.insert_unique(9);
	tree.insert_equal(1);
	tree.insert_equal(9);
	tree.insert_unique(1);
	EXPECT_EQ(4, tree.size());
}

TEST(SplayTree, Erase) {
SplayTree<int> tree{3, 1, 5, 4, 2, 2, 4, 4, 2, 4, 2};
	tree.erase(4);
	tree.erase(2);
	EXPECT_EQ(9, accumulate(tree.begin(), tree.end(), 0));
}