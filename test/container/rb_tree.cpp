#include "../test.hpp"
#include <libbr/container/rb_tree.hpp>
#include <libbr/algorithm/accumulate.hpp>
#include <libbr/iterator/begin.hpp>
#include <libbr/iterator/end.hpp>

using namespace BR;

template class BR::RBTree<int>;

TEST(RBTree, DefaultConstruct) {
	RBTree<int> tree;
	EXPECT_EQ(0, tree.size());
}

TEST(RBTree, InitializerListConstruct) {
	RBTree<int> tree{1, 2, 3, 4, 5, 6, 7, 8, 9};
	ASSERT_TRUE(tree.verify());
	EXPECT_EQ(9, tree.size());
	EXPECT_EQ(45, accumulate(tree.begin(), tree.end(), 0));
}

TEST(RBTree, RangeConstruct) {
	int values[9] = { 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	RBTree<int> tree(begin(values), end(values));
	ASSERT_TRUE(tree.verify());
	EXPECT_EQ(9, tree.size());
}

TEST(RBTree, InsertEqual) {
	int values[9] = { 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	RBTree<int> tree;
	tree.insert_equal(begin(values), end(values));
	ASSERT_TRUE(tree.verify());
	EXPECT_EQ(9, tree.size());
}

TEST(RBTree, CopyConstruct) {
	RBTree<int> tree0{ 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	ASSERT_TRUE(tree0.verify());
	RBTree<int> tree1(tree0);
	ASSERT_TRUE(tree1.verify());
	EXPECT_EQ(9, tree0.size());
	EXPECT_EQ(9, tree1.size());
}

TEST(RBTree, MoveConstruct) {
	RBTree<int> tree0{ 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	ASSERT_TRUE(tree0.verify());
	RBTree<int> tree1(move(tree0));
	ASSERT_TRUE(tree1.verify());
	EXPECT_EQ(0, tree0.size());
	EXPECT_EQ(9, tree1.size());
}

TEST(RBTree, Insert) {
	RBTree<int> tree{5};
	ASSERT_TRUE(tree.verify());
	tree.insert_unique(9);
	ASSERT_TRUE(tree.verify());
	tree.insert_equal(1);
	ASSERT_TRUE(tree.verify());
	tree.insert_equal(9);
	ASSERT_TRUE(tree.verify());
	tree.insert_unique(1);
	ASSERT_TRUE(tree.verify());
	EXPECT_EQ(4, tree.size());
}

TEST(RBTree, Erase) {
	RBTree<int> tree{3, 1, 5, 4, 2, 2, 4, 4, 2, 4, 2};
	ASSERT_TRUE(tree.verify());
	tree.erase(4);
	ASSERT_TRUE(tree.verify());
	tree.erase(2);
	ASSERT_TRUE(tree.verify());
	EXPECT_EQ(9, accumulate(tree.begin(), tree.end(), 0));
}