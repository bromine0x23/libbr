#include "../test.hpp"
#include <libbr/memory/uninitialized_construct_n.hpp>

#include <libbr/algorithm/all_of.hpp>
#include <libbr/algorithm/count.hpp>
#include <libbr/container/dlist.hpp>
#include <libbr/container/dynamic_array.hpp>
#include <libbr/container/fixed_array.hpp>

using namespace BR;

TEST(Memory, uninitialized_construct_n) {
	static constexpr auto dimension = 9U;
	{

		DynamicArray< FixedArray<int, dimension> > matrix;

		matrix.reserve(dimension);

		uninitialized_construct_n(matrix.begin(), dimension);

		auto result = all_of(matrix.cbegin(), matrix.cbegin() + dimension, [dimension](FixedArray<int, dimension> const & row){
			return count(row.cbegin(), row.cend(), 0) == dimension;
		});

		EXPECT_TRUE(result);
	} {
		auto value = 5;

		DynamicArray< DList<int> > matrix;

		matrix.reserve(dimension);

		uninitialized_construct_n(matrix.begin(), dimension, value, dimension);

		auto result = all_of(matrix.cbegin(), matrix.cbegin() + dimension, [value, dimension](DList<int> const & row){
			return count(row.cbegin(), row.cend(), value) == dimension;
		});

		EXPECT_TRUE(result);
	}
}