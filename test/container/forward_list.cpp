#include "../test.hpp"
#include <libbr/container/forward_list.hpp>
#include <libbr/string/raw_string.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/utility/move.hpp>

using namespace BR;

static bool is_even(int v) {
	return v % 2 == 0;
}

#if defined(BR_DEBUG)
template class BR::ForwardList<int>;
#endif

TEST(ForwardList, construct) {
	ForwardList< RawString<char> > words0{ "the", "frogurt", "is", "also", "cursed" };

	ForwardList< RawString<char> > words1(words0.begin(), words0.end());

	ForwardList< RawString<char> > words2(words0);

	ForwardList< RawString<char> > words3("Mo", 5);
}

TEST(ForwardList, each) {

	ForwardList<int> list{ 0, 1, 2, 3, 4 };

	list.each();

	EXPECT_TRUE(list.any(is_even));
	EXPECT_FALSE(list.all(is_even));
	EXPECT_FALSE(list.none(is_even));
	EXPECT_TRUE(list.include(2));
	EXPECT_FALSE(list.include(8));
}

TEST(ForwardList, assign) {
	ForwardList<int> list0{ 3, 1, 4, 6, 5, 9 };

	ForwardList<int> list1;

	list1 = list0;

	EXPECT_EQ((ForwardList<int>{ 3, 1, 4, 6, 5, 9 }), list0);

	ForwardList<int> list2;

	list2 = move(list0);

	EXPECT_EQ((ForwardList<int>{}), list0);

	EXPECT_EQ((ForwardList<int>{ 3, 1, 4, 6, 5, 9 }), list2);

	list0.assign(10, 5);

	EXPECT_EQ((ForwardList<int>{ 10, 10, 10, 10, 10 }), list0);

	list1.assign(list0.begin(), list0.end());

	EXPECT_EQ((ForwardList<int>{ 10, 10, 10, 10, 10 }), list1);

}

TEST(ForwardList, insert) {
	ForwardList<int> list{ 0, 1, 2, 3, 4 };

	list.insert_front(5);

	EXPECT_EQ((ForwardList<int>{ 5, 0, 1, 2, 3, 4 }), list);

	list.insert_after(list.cbegin(), 6);

	EXPECT_EQ((ForwardList<int>{ 5, 6, 0, 1, 2, 3, 4 }), list);

	list.insert_after(next(list.before_cbegin(), 4), 7, 2);

	EXPECT_EQ((ForwardList<int>{ 5, 6, 0, 1, 7, 7, 2, 3, 4 }), list);

	ForwardList<int> to_insert{ 8, 9 };

	list.insert_after(next(list.before_cbegin(), 3), to_insert.begin(), to_insert.end());

	EXPECT_EQ((ForwardList<int>{ 5, 6, 0, 8, 9, 1, 7, 7, 2, 3, 4 }), list);

	list.insert_after(next(list.before_cbegin(), 4), { 10, 11, 12 });

	EXPECT_EQ((ForwardList<int>{ 5, 6, 0, 8, 10, 11, 12, 9, 1, 7, 7, 2, 3, 4 }), list);
}

TEST(ForwardList, erase) {
	ForwardList<int> list{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	list.erase_front();

	EXPECT_EQ((ForwardList<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }), list);

	list.erase_after(list.cbegin());

	EXPECT_EQ((ForwardList<int>{ 1, 3, 4, 5, 6, 7, 8, 9 }), list);

	list.erase_after(next(list.cbegin()), next(list.cbegin(), 4));

	EXPECT_EQ((ForwardList<int>{ 1, 3, 6, 7, 8, 9 }), list);
}

TEST(ForwardList, remove) {
	ForwardList<int> list{ 1, 100, 2, 3, 10, 1, 11, -1, 12 };

	list.remove(1);

	EXPECT_EQ((ForwardList<int>{ 100, 2, 3, 10, 11, -1, 12 }), list);

	list.remove_if([](int n){ return n > 10; });

	EXPECT_EQ((ForwardList<int>{ 2, 3, 10, -1 }), list);
}

TEST(ForwardList, splice_after) {
	ForwardList<int> list0{ 0, 1, 2, 3, 4 };
	ForwardList<int> list1{ 10, 11, 12 };

	list1.splice_after(list1.cbegin(), list0, list0.cbegin(), list0.cend());

	EXPECT_EQ((ForwardList<int>{ 0 }), list0);
	EXPECT_EQ((ForwardList<int>{ 10, 1, 2, 3, 4, 11, 12 }), list1);

	list0.splice_after(list0.cbegin(), list1, next(list1.cbegin(), 2));

	EXPECT_EQ((ForwardList<int>{ 0, 3 }), list0);
	EXPECT_EQ((ForwardList<int>{ 10, 1, 2, 4, 11, 12 }), list1);

	list1.splice_after(list1.cbegin(), list0);

	EXPECT_TRUE(list0.empty());
	EXPECT_EQ((ForwardList<int>{ 10, 0, 3, 1, 2, 4, 11, 12 }), list1);
}

TEST(ForwardList, unique) {
	ForwardList<int> list{ 1, 2, 2, 3, 3, 2, 1, 1, 2 };

	list.unique();

	EXPECT_EQ((ForwardList<int>{ 1, 2, 3, 2, 1, 2 }), list);
}

TEST(ForwardList, merge) {
	ForwardList<int> list0{ 0, 1, 3, 5, 9 };
	ForwardList<int> list1{ 2, 4, 6, 7, 8 };

	list0.merge(list1);

	EXPECT_EQ((ForwardList<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }), list0);
}

TEST(ForwardList, sort) {
	ForwardList<int> list{ 31, 17, 14, 19, 20, 8, 10, 22, 30, 15, 21, 1, 4, 6, 3, 5, 11, 9, 23, 2, 12, 0, 29, 18, 28, 16, 26, 25, 7, 27, 24, 13 };

	list.sort();

	EXPECT_EQ((ForwardList<int>{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 }), list);
}

TEST(ForwardList, reverse) {
	ForwardList<int> list{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	list.reverse();

	EXPECT_EQ((ForwardList<int>{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }), list);
}

