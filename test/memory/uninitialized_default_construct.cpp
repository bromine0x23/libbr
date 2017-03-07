#include "../test.hpp"
#include <libbr/memory/uninitialized_default_construct.hpp>

#include <libbr/algorithm/all_of.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/fixed_array.hpp>

using namespace BR;

namespace {

struct S {

	int i;

	S() : i(9) {}
};

}

TEST(Memory, uninitialized_default_construct) {
	DynamicArray< FixedArray<S, 5> > matrix;

	auto count = 9U;

	matrix.reserve(count);

	uninitialized_default_construct(matrix.begin(), matrix.begin() + count);

	auto result = all_of(matrix.cbegin(), matrix.cbegin() + count, [](auto const & row){
		return all_of(row.cbegin(), row.cend(), [](auto x){ return x.i == 9; });
	});

	EXPECT_TRUE(result);
}