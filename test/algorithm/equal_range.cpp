#include "../test.hpp"
#include <libbr/algorithm/equal_range.hpp>

#include <libbr/algorithm/all_of.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>

using namespace BR;

struct S {
	int number;
	char name;

	S(int number, char name) : number(number), name(name) {}

	auto operator<(S const & s) const -> bool {
		return number < s.number;
	}
};

struct Comparator {
	auto operator()(S const s, int i) -> bool {
		return s.number < i;
	}
	auto operator()(int i, S const & s) -> bool {
		return i < s.number;
	}
};

TEST(Algorithm, equal_range) {
	{
		DynamicArray<S> array{ { 1, 'A' }, { 2, 'B' }, { 2, 'C' }, { 2, 'D' }, { 3, 'G' }, { 4, 'F' } };
		{
			auto pair = equal_range(array.cbegin(), array.cend(), S( 2, '?' ));

			EXPECT_TRUE(all_of(pair.first, pair.second, [](S s){ return s.number == 2; }));
		} {
			auto pair = equal_range(array.cbegin(), array.cend(), 2, Comparator());

			EXPECT_TRUE(all_of(pair.first, pair.second, [](S s){ return s.number == 2; }));
		}
	} {
		DList<S> list{ { 1, 'A' }, { 2, 'B' }, { 2, 'C' }, { 2, 'D' }, { 3, 'G' }, { 4, 'F' } };
		{
			auto pair = equal_range(list.cbegin(), list.cend(), S( 2, '?' ));

			EXPECT_TRUE(all_of(pair.first, pair.second, [](S s){ return s.number == 2; }));
		} {
			auto pair = equal_range(list.cbegin(), list.cend(), 2, Comparator());

			EXPECT_TRUE(all_of(pair.first, pair.second, [](S s){ return s.number == 2; }));
		}
	} {
		SList<S> list{ { 1, 'A' }, { 2, 'B' }, { 2, 'C' }, { 2, 'D' }, { 3, 'G' }, { 4, 'F' } };
		{
			auto pair = equal_range(list.cbegin(), list.cend(), S( 2, '?' ));

			EXPECT_TRUE(all_of(pair.first, pair.second, [](S s){ return s.number == 2; }));
		} {
			auto pair = equal_range(list.cbegin(), list.cend(), 2, Comparator());

			EXPECT_TRUE(all_of(pair.first, pair.second, [](S s){ return s.number == 2; }));
		}
	}
}
