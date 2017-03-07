#include "../test.hpp"
#include <libbr/memory/uninitialized_copy.hpp>

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

	auto operator==(S const & s) const -> bool { return i == s.i; }
};

}

TEST(Memory, uninitialized_copy) {
	{
		FixedArray<int, 9> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		FixedArray<int, 9> to_array;

		uninitialized_copy(from_array.cbegin(), from_array.cend(), to_array.begin());

		EXPECT_EQ((FixedArray<int, 9>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }), to_array);
	} {
		DynamicArray<int> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		FixedArray<int, 9> to_array;

		uninitialized_copy(from_array.cbegin(), from_array.cend(), to_array.begin());

		EXPECT_EQ((FixedArray<int, 9>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }), to_array);
	} {
		DList<int> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		FixedArray<int, 9> to_array;

		uninitialized_copy(from_list.cbegin(), from_list.cend(), to_array.begin());

		EXPECT_EQ((FixedArray<int, 9>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }), to_array);
	} {
		FixedArray<S, 9> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		FixedArray<S, 9> to_array;

		uninitialized_copy(from_array.cbegin(), from_array.cend(), to_array.begin());

		EXPECT_EQ((FixedArray<S, 9>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }), to_array);
	} {
		DynamicArray<S> from_array{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		FixedArray<S, 9> to_array;

		uninitialized_copy(from_array.cbegin(), from_array.cend(), to_array.begin());

		EXPECT_EQ((FixedArray<S, 9>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }), to_array);
	} {
		DList<S> from_list{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		FixedArray<S, 9> to_array;

		uninitialized_copy(from_list.cbegin(), from_list.cend(), to_array.begin());

		EXPECT_EQ((FixedArray<S, 9>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 }), to_array);
	}
}