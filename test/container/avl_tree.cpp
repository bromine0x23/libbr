#include "../test.hpp"
#include <libbr/container/avl_tree.hpp>
#include <libbr/algorithm/accumulate.hpp>
#include <libbr/iterator/begin.hpp>
#include <libbr/iterator/end.hpp>

using namespace BR;

#if defined(BR_DEBUG)
template class BR::AVLTree<int>;
#endif

TEST(AVLTree, DefaultConstruct) {
	AVLTree<int> tree;
	EXPECT_EQ(0, tree.size());
}

TEST(AVLTree, InitializerListConstruct) {
	AVLTree<int> tree{1, 2, 3, 4, 5, 6, 7, 8, 9};
	EXPECT_EQ(9, tree.size());
	EXPECT_EQ(45, accumulate(tree.begin(), tree.end(), 0));
}

TEST(AVLTree, RangeConstruct) {
	int values[9] = { 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	AVLTree<int> tree(begin(values), end(values));
	EXPECT_EQ(9, tree.size());
}

TEST(AVLTree, InsertEqual) {
	int values[9] = { 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	AVLTree<int> tree;
	tree.insert_equal(begin(values), end(values));
	EXPECT_EQ(9, tree.size());
}

TEST(AVLTree, CopyConstruct) {
	AVLTree<int> tree0{ 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	AVLTree<int> tree1(tree0);
	EXPECT_EQ(9, tree0.size());
	EXPECT_EQ(9, tree1.size());
}

TEST(AVLTree, MoveConstruct) {
	AVLTree<int> tree0{ 1, 3, 5, 7, 9, 8, 6, 4, 2 };
	AVLTree<int> tree1(move(tree0));
	EXPECT_EQ(0, tree0.size());
	EXPECT_EQ(9, tree1.size());
}

TEST(AVLTree, Insert) {
	AVLTree<int> tree{5};
	tree.insert_unique(9);
	tree.insert_equal(1);
	tree.insert_equal(9);
	tree.insert_unique(1);
	EXPECT_EQ(4, tree.size());
}

TEST(AVLTree, Erase) {
	AVLTree<int> tree{3, 1, 5, 4, 2, 2, 4, 4, 2, 4, 2};
	tree.erase(4);
	tree.erase(2);
	EXPECT_EQ(9, accumulate(tree.begin(), tree.end(), 0));
}

TEST(AVLTree, Merge) {
	AVLTree<int> tree0{1, 3, 5, 7, 9};
	AVLTree<int> tree1{2, 4, 6, 8, 10};

	tree0.merge_equal(tree1);
	EXPECT_EQ(55, accumulate(tree0.begin(), tree0.end(), 0));
	EXPECT_EQ(0, accumulate(tree1.begin(), tree1.end(), 0));
}