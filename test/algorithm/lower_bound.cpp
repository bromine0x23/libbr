#include "../test.hpp"
#include <libbr/algorithm/lower_bound.hpp>

#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/slist.hpp>
#include <libbr/iterator/distance.hpp>

using namespace BR;

struct S {
	int i;
	char c;

	S(int i, char c) : i(i), c(c) {}

	auto operator<(S const & s) const -> bool {
		return i < s.i;
	}
};

struct Comparator {
	auto operator()(S const s, int i) -> bool {
		return s.i < i;
	}
	auto operator()(int i, S const & s) -> bool {
		return i < s.i;
	}
};

TEST(Algorithm, lower_bound) {
	{
		DynamicArray<S> array{ { 1, 'A' }, { 2, 'B' }, { 2, 'C' }, { 2, 'D' }, { 3, 'G' }, { 4, 'F' } };
		{
			auto lower = lower_bound(array.cbegin(), array.cend(), S( 2, '?' ));

			EXPECT_EQ(2, lower->i);

			EXPECT_EQ(1, distance(array.cbegin(), lower));
		} {
			auto lower = lower_bound(array.cbegin(), array.cend(), 2, Comparator());

			EXPECT_EQ(2, lower->i);

			EXPECT_EQ(1, distance(array.cbegin(), lower));
		}
	} {
		DList<S> list{ { 1, 'A' }, { 2, 'B' }, { 2, 'C' }, { 2, 'D' }, { 3, 'G' }, { 4, 'F' } };
		{
			auto lower = lower_bound(list.cbegin(), list.cend(), S( 2, '?' ));

			EXPECT_EQ(2, lower->i);

			EXPECT_EQ(1, distance(list.cbegin(), lower));
		} {
			auto lower = lower_bound(list.cbegin(), list.cend(), 2, Comparator());

			EXPECT_EQ(2, lower->i);

			EXPECT_EQ(1, distance(list.cbegin(), lower));
		}
	} {
		SList<S> list{ { 1, 'A' }, { 2, 'B' }, { 2, 'C' }, { 2, 'D' }, { 3, 'G' }, { 4, 'F' } };
		{
			auto lower = lower_bound(list.cbegin(), list.cend(), S( 2, '?' ));

			EXPECT_EQ(2, lower->i);

			EXPECT_EQ(1, distance(list.cbegin(), lower));
		} {
			auto lower = lower_bound(list.cbegin(), list.cend(), 2, Comparator());

			EXPECT_EQ(2, lower->i);

			EXPECT_EQ(1, distance(list.cbegin(), lower));
		}
	}
}
