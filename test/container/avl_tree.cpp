#include "../test.hpp"
#include <libbr/container/avl_tree.hpp>
#include <libbr/algorithm/accumulate.hpp>
#include <libbr/iterator/begin.hpp>
#include <libbr/iterator/end.hpp>

using namespace BR;

template class BR::AVLTree<int>;

TEST(AVLTree, DefaultConstruct) {
	AVLTree<int> tree;
	EXPECT_EQ(0, tree.size());
}

TEST(AVLTree, InitializerListConstruct) {
	AVLTree<int> tree{1, 2, 3, 4, 5, 6, 7, 8, 9};
	ASSERT_TRUE(tree.verify());
	EXPECT_EQ(9, tree.size());
	EXPECT_EQ(45, accumulate(tree.begin(), tree.end(), 0));
}

TEST(AVLTree, RangeConstruct) {
	int values[9] = { 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	AVLTree<int> tree(begin(values), end(values));
	ASSERT_TRUE(tree.verify());
	EXPECT_EQ(9, tree.size());
}

TEST(AVLTree, InsertEqual) {
	int values[9] = { 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	AVLTree<int> tree;
	tree.insert_equal(begin(values), end(values));
	ASSERT_TRUE(tree.verify());
	EXPECT_EQ(9, tree.size());
}

TEST(AVLTree, CopyConstruct) {
	AVLTree<int> tree0{ 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	ASSERT_TRUE(tree0.verify());
	AVLTree<int> tree1(tree0);
	ASSERT_TRUE(tree1.verify());
	EXPECT_EQ(9, tree0.size());
	EXPECT_EQ(9, tree1.size());
}

TEST(AVLTree, MoveConstruct) {
	AVLTree<int> tree0{ 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	ASSERT_TRUE(tree0.verify());
	AVLTree<int> tree1(move(tree0));
	ASSERT_TRUE(tree1.verify());
	EXPECT_EQ(0, tree0.size());
	EXPECT_EQ(9, tree1.size());
}

TEST(AVLTree, Insert) {
	AVLTree<int> tree{5};
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

TEST(AVLTree, Erase) {
	AVLTree<int> tree{3, 1, 5, 4, 2, 2, 4, 4, 2, 4, 2};
	ASSERT_TRUE(tree.verify());
	tree.erase(4);
	ASSERT_TRUE(tree.verify());
	tree.erase(2);
	ASSERT_TRUE(tree.verify());
	EXPECT_EQ(9, accumulate(tree.begin(), tree.end(), 0));
}