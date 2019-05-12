#include "test.hpp"

#include<libbr/type_traits/integer_traits.hpp>

using namespace BR;

TEST(TypeTraits, IntegerTraits) {
	EXPECT_TRUE(IntegerTraits<signed int>::is_integer);
	EXPECT_TRUE(IntegerTraits<signed int>::is_signed);
	EXPECT_LT(IntegerTraits<signed int>::min(), IntegerTraits<signed int>::max());
	EXPECT_GT(0, IntegerTraits<signed int>::min());
	EXPECT_LT(0, IntegerTraits<signed int>::max());

	EXPECT_TRUE(IntegerTraits<unsigned int>::is_integer);
	EXPECT_FALSE(IntegerTraits<unsigned int>::is_signed);
	EXPECT_LT(IntegerTraits<unsigned int>::min(), IntegerTraits<unsigned int>::max());
	EXPECT_EQ(0, IntegerTraits<unsigned int>::min());
	EXPECT_LT(0, IntegerTraits<unsigned int>::max());

	EXPECT_TRUE(IntegerTraits<bool>::is_integer);
	EXPECT_FALSE(IntegerTraits<bool>::is_signed);
	EXPECT_LT(IntegerTraits<bool>::min(), IntegerTraits<bool>::max());
}