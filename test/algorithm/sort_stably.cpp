#include "../test.hpp"
#include <libbr/algorithm/sort_stably.hpp>

#include <libbr/container/dynamic_array.hpp>

using namespace BR;

struct S {
	int i;
	char c;

	S(int i, char c) : i(i), c(c) {}

	auto operator<(S const & s) const -> bool {
		return i < s.i;
	}

	auto operator==(S const & s) const -> bool {
		return i == s.i && c == s.c;
	}
};

TEST(Algorithm, sort_stably) {
	DynamicArray<S> array{ { 4, 'A' }, { 2, 'B' }, { 3, 'C' }, { 1, 'D' }, { 2, 'E' }, { 2, 'F' } };

	sort_stably(array.begin(), array.end());

	EXPECT_EQ((DynamicArray<S>{ { 1, 'D' }, { 2, 'B' }, { 2, 'E' }, { 2, 'F' }, { 3, 'C' }, { 4, 'A' } }), array);
}
