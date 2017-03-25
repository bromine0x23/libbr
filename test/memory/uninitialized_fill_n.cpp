#include "../test.hpp"
#include <libbr/memory/uninitialized_fill_n.hpp>

#include <libbr/algorithm/count.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/fixed_array.hpp>

using namespace BR;

namespace {

struct S {

	int x;

	S() = default;

	S(int x) : x(x) {}

	S(S const & s) : x(s.x) {}

	auto operator==(S const & s) const -> bool { return x == s.x; }
};

}

TEST(Memory, uninitialized_fill_n) {
	{
		FixedArray<int, 9> array{{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }};

		uninitialized_fill_n(array.begin(), 5, 0);

		EXPECT_EQ(5, count(array.cbegin(), array.cend(), 0));
	} {
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		uninitialized_fill_n(array.begin(), 5, 0);

		EXPECT_EQ(5, count(array.cbegin(), array.cend(), 0));
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		uninitialized_fill_n(list.begin(), 5, 0);

		EXPECT_EQ(5, count(list.cbegin(), list.cend(), 0));
	} {
		FixedArray<S, 9> array{{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }};

		uninitialized_fill_n(array.begin(), 5, 0);

		EXPECT_EQ(5, count(array.cbegin(), array.cend(), 0));
	} {
		DynamicArray<S> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		uninitialized_fill_n(array.begin(), 5, 0);

		EXPECT_EQ(5, count(array.cbegin(), array.cend(), 0));
	} {
		DList<S> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		uninitialized_fill_n(list.begin(), 5, 0);

		EXPECT_EQ(5, count(list.cbegin(), list.cend(), 0));
	}
}