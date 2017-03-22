#include "../test.hpp"
#include <libbr/memory/uninitialized_construct.hpp>

#include <libbr/algorithm/all_of.hpp>
#include <libbr/algorithm/count.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/fixed_array.hpp>

using namespace BR;

TEST(Memory, uninitialized_construct) {
	static constexpr auto dimension = 9U;
	{
		DynamicArray< FixedArray<int, dimension> > matrix;

		matrix.reserve(dimension);

		uninitialized_construct(matrix.begin(), matrix.begin() + dimension);

		auto result = all_of(matrix.cbegin(), matrix.cbegin() + dimension, [](FixedArray<int, dimension> const & row) {
			return count(row.cbegin(), row.cend(), 0) == dimension;
		});

		EXPECT_TRUE(result);
	} {
		auto value = 5;

		DynamicArray< DList<int> > matrix;

		matrix.reserve(dimension);

		uninitialized_construct(matrix.begin(), matrix.begin() + dimension, value, dimension);

		auto result = all_of(matrix.cbegin(), matrix.cbegin() + dimension, [value](DList<int> const & row) {
			return count(row.cbegin(), row.cend(), value) == dimension;
		});

		EXPECT_TRUE(result);
	}
}