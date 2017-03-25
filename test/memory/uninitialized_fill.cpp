#include "../test.hpp"
#include <libbr/memory/uninitialized_fill.hpp>

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

TEST(Memory, uninitialized_fill) {
	{
		FixedArray<int, 9> array({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });

		uninitialized_fill(array.begin(), array.end(), 0);

		EXPECT_EQ(9, count(array.cbegin(), array.cend(), 0));
	} {
		DynamicArray<int> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		uninitialized_fill(array.begin(), array.end(), 0);

		EXPECT_EQ(9, count(array.cbegin(), array.cend(), 0));
	} {
		DList<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		uninitialized_fill(list.begin(), list.end(), 0);

		EXPECT_EQ(9, count(list.cbegin(), list.cend(), 0));
	} {
		FixedArray<S, 9> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		uninitialized_fill(array.begin(), array.end(), 0);

		EXPECT_EQ(9, count(array.cbegin(), array.cend(), 0));
	} {
		DynamicArray<S> array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		uninitialized_fill(array.begin(), array.end(), 0);

		EXPECT_EQ(9, count(array.cbegin(), array.cend(), 0));
	} {
		DList<S> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		uninitialized_fill(list.begin(), list.end(), 0);

		EXPECT_EQ(9, count(list.cbegin(), list.cend(), 0));
	}
}