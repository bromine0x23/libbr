#include "../test.hpp"
#include <libbr/memory/uninitialized_move_n.hpp>

#include <libbr/algorithm/count.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/fixed_array.hpp>
#include <libbr/iterator/insert_back_iterator.hpp>

using namespace BR;

namespace {

struct S {

	int i;

	S() = default;

	S(int i) : i(i) {}

	S(S const & s) : i(s.i) {}

	S(S && s) : i(s.i) { s.i = 0; }

	auto operator==(S const & s) const -> bool { return i == s.i; }
};

}

TEST(Memory, uninitialized_move_n) {
	{
		FixedArray<S, 9> from_array{{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }};

		FixedArray<S, 9> to_array;

		uninitialized_move_n(from_array.begin(), from_array.size(), to_array.begin());

		EXPECT_EQ(9, count(from_array.cbegin(), from_array.cend(), 0));

		EXPECT_EQ((FixedArray<S, 9>{{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }}), to_array);
	} {
		DynamicArray<S> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		FixedArray<S, 9> to_array;

		uninitialized_move_n(from_array.begin(), from_array.size(), to_array.begin());

		EXPECT_EQ(9, count(from_array.cbegin(), from_array.cend(), 0));

		EXPECT_EQ((FixedArray<S, 9>{{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }}), to_array);
	} {
		DList<S> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		FixedArray<S, 9> to_array;

		uninitialized_move_n(from_list.begin(), from_list.size(), to_array.begin());

		EXPECT_EQ(9, count(from_list.cbegin(), from_list.cend(), 0));

		EXPECT_EQ((FixedArray<S, 9>{{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }}), to_array);
	}
}