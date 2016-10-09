#include "test.hpp"

#include<libbr/type_traits/rank.hpp>

using namespace BR;

TEST(TypeTraits, Rank) {
	INTEGRAL_CHECK(0, Rank, rank, int);
	INTEGRAL_CHECK(1, Rank, rank, int[]);
	INTEGRAL_CHECK(2, Rank, rank, int[][3]);
	INTEGRAL_CHECK(2, Rank, rank, int[2][3]);
	INTEGRAL_CHECK(3, Rank, rank, int[2][3][5]);
	INTEGRAL_CHECK(0, Rank, rank, int(*)[2][3]);
	INTEGRAL_CHECK(0, Rank, rank, int(&)[2][3]);
	INTEGRAL_CHECK(0, Rank, rank, int(&&)[2][3]);
}