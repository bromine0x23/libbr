#include "../test.hpp"
#include <libbr/container/binary_tree.hpp>
#include <libbr/algorithm/accumulate.hpp>
#include <libbr/iterator/begin.hpp>
#include <libbr/iterator/end.hpp>
#include <iostream>

using namespace BR;

#if defined(BR_DEBUG)
template class BR::BinaryTree<int>;
#endif

TEST(BinaryTree, DefaultConstruct) {
	BinaryTree<int> tree;
	EXPECT_EQ(0, tree.size());
}

TEST(BinaryTree, InitializerListConstruct) {
	BinaryTree<int> tree{1, 2, 3, 4, 5, 6, 7, 8, 9};
	EXPECT_EQ(9, tree.size());
}

TEST(BinaryTree, RangeConstruct) {
	int values[9] = { 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	BinaryTree<int> tree(begin(values), end(values));
	EXPECT_EQ(9, tree.size());
}

TEST(BinaryTree, CopyConstruct) {
	BinaryTree<int> tree0{ 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	BinaryTree<int> tree1 = tree0;
	EXPECT_EQ(9, tree0.size());
	EXPECT_EQ(9, tree1.size());
}

TEST(BinaryTree, MoveConstruct) {
	BinaryTree<int> tree0{ 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	BinaryTree<int> tree1(move(tree0));
	EXPECT_EQ(0, tree0.size());
	EXPECT_EQ(9, tree1.size());
}

TEST(BinaryTree, Insert) {
	BinaryTree<int> tree{5};
	tree.insert_unique(9);
	tree.insert_equal(1);
	tree.insert_equal(9);
	tree.insert_unique(1);
	EXPECT_EQ(4, tree.size());
}

TEST(BinaryTree, Erase) {
	BinaryTree<int> tree{3, 1, 5, 4, 2, 2, 4, 4, 2, 4, 2};
	tree.erase(4);
	tree.erase(2);
	EXPECT_EQ(9, accumulate(tree.begin(), tree.end(), 0));
}

TEST(BinaryTree, Merge) {
	BinaryTree<int> tree0{1, 3, 5, 7, 9};
	BinaryTree<int> tree1{2, 4, 6, 8, 10};

	tree0.merge_equal(tree1);
	EXPECT_EQ(55, accumulate(tree0.begin(), tree0.end(), 0));
	EXPECT_EQ(0, accumulate(tree1.begin(), tree1.end(), 0));
}