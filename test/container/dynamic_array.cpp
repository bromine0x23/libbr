#include "../test.hpp"
#include <libbr/container/dynamic_array.hpp>
#include <libbr/iterator/next.hpp>
#include <libbr/string/raw_string.hpp>

using namespace BR;

#if defined(BR_DEBUG)
template class BR::DynamicArray< int >;
#endif

TEST(DynamicArray, construct) {
	DynamicArray< RawString<char> > words0{ "the", "frogurt", "is", "also", "cursed" };

	DynamicArray< RawString<char> > words1(words0.begin(), words0.end());

	DynamicArray< RawString<char> > words2(words0);

	DynamicArray< RawString<char> > words3("Mo", 5);

	BR_FORCE_USE(words0);
}

TEST(DynamicArray, insert) {

	DynamicArray<int> array{ 0, 1, 2, 3, 4 };

	std::printf("%d %d\n", array.front(), array.back());

	array.insert(array.cbegin(), 5);

	std::printf("%d %d\n", array.front(), array.back());

	EXPECT_EQ((DynamicArray<int>{ 5, 0, 1, 2, 3, 4 }), array);

	array.insert(next(array.cbegin()), 6);

	EXPECT_EQ((DynamicArray<int>{ 5, 6, 0, 1, 2, 3, 4 }), array);

	array.insert(next(array.cbegin(), 4), 7, 2);

	EXPECT_EQ((DynamicArray<int>{ 5, 6, 0, 1, 7, 7, 2, 3, 4 }), array);

	DynamicArray<int> to_insert{ 8, 9 };

	array.insert(next(array.cbegin(), 3), to_insert.begin(), to_insert.end());

	EXPECT_EQ((DynamicArray<int>{ 5, 6, 0, 8, 9, 1, 7, 7, 2, 3, 4 }), array);

	array.insert(next(array.cbegin(), 4), { 10, 11, 12 });

	EXPECT_EQ((DynamicArray<int>{ 5, 6, 0, 8, 10, 11, 12, 9, 1, 7, 7, 2, 3, 4 }), array);

	array.insert_back(13);

	EXPECT_EQ((DynamicArray<int>{ 5, 6, 0, 8, 10, 11, 12, 9, 1, 7, 7, 2, 3, 4, 13 }), array);
}

TEST(DynamicArray, erase) {
	DynamicArray<int> list{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	list.erase(list.cbegin());

	EXPECT_EQ((DynamicArray<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }), list);

	list.erase(next(list.cbegin()));

	EXPECT_EQ((DynamicArray<int>{ 1, 3, 4, 5, 6, 7, 8, 9 }), list);

	list.erase(next(list.cbegin()), next(list.cbegin(), 3));

	EXPECT_EQ((DynamicArray<int>{ 1, 5, 6, 7, 8, 9 }), list);

	list.erase_back();

	EXPECT_EQ((DynamicArray<int>{ 1, 5, 6, 7, 8 }), list);
}